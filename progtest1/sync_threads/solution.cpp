#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <climits>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <deque>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include "progtest_solver.h"
#include "sample_tester.h"
using namespace std;
#endif /* __PROGTEST__ */

class CWeldingCompany
{
public:
    static void SeqSolve(APriceList priceList, COrder& order)
    {
        std::vector<COrder> v = {order};
        ProgtestSolver(v, priceList);
        order = v.front();
    }

    void AddProducer(AProducer prod)
    {
        producers.emplace_back(prod);
        nProducers++;
    }

    void AddCustomer(ACustomer cust)
    {
        customers.emplace_back(cust);
        nCustomers++;
    }

    /*
     * This method inserts a producer and his price list by a particular ID into a map.
     * Checks if a material is found in a map.
     */
    void AddPriceList(AProducer prod, APriceList priceList)
    {
        unsigned int materialID = priceList.get()->m_MaterialID;

        std::unique_lock<std::mutex> lockerMap(mtxMapPriceLists);
        if(dbsPriceLists.count(materialID))
        {
            dbsPriceLists.at(materialID).first.insert(prod);
            dbsPriceLists.at(materialID).second.insert(priceList);
        }
        else
        {
            lockerMap.unlock();
            std::set<AProducer> producers;
            std::set<APriceList> priceLists;
            producers.insert(prod);
            priceLists.insert(priceList);
            lockerMap.lock();

            dbsPriceLists[materialID] = std::make_pair(producers, priceLists);
        }

        //maybe notify_all? IDK
        cvMapNotAllProd.notify_one();
    }

    void Start(unsigned thrCount)
    {
        nProdThreads = thrCount;

        for(uint c = 0; c < nCustomers; c++)
            customerThreads.emplace_back(std::thread(&CWeldingCompany::handleDemands, this, std::ref(customers.at(c))));

        for(uint p = 0; p < nProdThreads; p++)
            producerThreads.emplace_back(std::thread(&CWeldingCompany::evaluateOrders, this));
    }

    void Stop()
    {
        for(auto& customerThr : customerThreads)
            customerThr.join();

        for(auto& producerThr : producerThreads)
            producerThr.join();
    }

private:
    /*
     * This method implements customer threads.
     */
    void handleDemands(const ACustomer& customer)
    {
        AOrderList orderList;

        while((orderList = customer.get()->WaitForDemand()) != nullptr)
        {
            std::unique_lock<std::mutex> lockC(mtxBuffer);
            cvFull.wait(lockC, [this] ()
            {
                return buffer.size() < nProdThreads;
            });

            buffer.push(std::make_pair(customer, orderList));
            cvEmpty.notify_one();
        }

        finishedCustomers++;
    }

    /*
     * The main thread serving for working purposes.
     */
    void evaluateOrders()
    {
        std::pair<ACustomer, AOrderList> orderList;
        std::unique_lock<std::mutex> lockP(mtxBuffer);

        while(!(buffer.empty() && finishedCustomers == nCustomers))
        {
            lockP.unlock();

            popBuffer(orderList);
            auto materialID = orderList.second.get()->m_MaterialID;

            lockP.lock();

            askProducers(materialID);

            APriceList tmpPriceList = std::make_shared<CPriceList>(materialID);
            createPriceList(materialID, tmpPriceList);

            APriceList cleanPriceList = std::make_shared<CPriceList>(materialID);
            removeDuplicates(tmpPriceList, cleanPriceList);

            for(auto& order : orderList.second.get()->m_List)
                SeqSolve(cleanPriceList, order);

            lockP.unlock();
            orderList.first.get()->Completed(orderList.second);
            lockP.lock();
        }
    }

    /*
     * Removes duplicates from a given price list. The way of doing that is inserting
     * each producer's item into a map, sorted by width and height in an ascending order.
     * If an item with the same size as an item being currently inserted
     * exists in the map, then prices are compared. If a price of a newly inserted item is
     * lower, then the original item is replaced. Returns a price list without duplicates.
     * Lower prices are preferred.
     */
    void removeDuplicates(const APriceList& priceList, APriceList& cleanPriceList)
    {
        using pairUint = std::pair<uint, uint>;
        auto cmp = [] (const pairUint& a, const pairUint&b)
        {
            return a.first == b.first ? a.second < b.second : a.first < b.first;
        };

        //<<width, height>, price>
        std::map<std::pair<uint, uint>, double, decltype(cmp)> m(cmp);

        for(const auto& item : priceList.get()->m_List)
        {
            uint min = std::min(item.m_W, item.m_H);
            uint max = std::max(item.m_W, item.m_H);
            std::pair<uint, uint> size = std::make_pair(min, max);

            if(m.count(size))
            {
                //double comparison
                double epsilon = 1024 * DBL_EPSILON * (std::fabs(m[size]) + std::fabs(item.m_Cost));
                if(m[size] - epsilon > item.m_Cost) m[size] = item.m_Cost;
                else;
            }
            else m[size] = item.m_Cost;
        }

        for(const auto& it : m)
            cleanPriceList.get()->Add(CProd(it.first.first, it.first.second, it.second));
    }

    /*
     * This method asks producers for sending their price lists.
     * Then, a thread waits until all producers will send their price lists.
     */
    void askProducers(const unsigned int& materialID)
    {
        bool contains = static_cast<bool>(dbsPriceLists.count(materialID)); // NOLINT
        bool complete = contains ? dbsPriceLists.at(materialID).first.size() == nProducers : false;

        if(!complete)
        {
            for(const auto& producer : producers)
                producer.get()->SendPriceList(materialID);
        }

        std::unique_lock<std::mutex> lockMap(mtxMapPriceLists);
        cvMapNotAllProd.wait(lockMap, [this, &contains, &materialID] ()
        {
            contains = static_cast<bool>(dbsPriceLists.count(materialID));
            return contains ? dbsPriceLists.at(materialID).first.size() == nProducers : false;
        });
    }

    /*
     * Merges all demands from all price lists by a particular material ID into a single price list.
     */
    void createPriceList(const unsigned int& materialID, const APriceList& tmp)
    {
        std::unique_lock<std::mutex> lockMap(mtxMapPriceLists);

        for(const auto& priceList : dbsPriceLists.at(materialID).second)
        {
            for(const auto& item : priceList.get()->m_List)
                tmp.get()->Add(item);
        }
    }

    /*
     * Pops a customer's order list from a shared buffer (implemented as a queue)
     */
    void popBuffer(std::pair<ACustomer, AOrderList>& orderList)
    {
        std::unique_lock<std::mutex> lockP(mtxBuffer);
        cvEmpty.wait(lockP, [this] ()
        {
            return !buffer.empty();
        });

        orderList = buffer.front();
        buffer.pop();
        cvFull.notify_one();
    }

    unsigned int nProducers = 0;
    unsigned int nCustomers = 0;
    unsigned int finishedCustomers = 0;
    unsigned int nProdThreads{};

    std::vector<AProducer> producers;
    std::vector<ACustomer> customers;

    std::vector<std::thread> customerThreads;
    std::vector<std::thread> producerThreads;

    std::queue<std::pair<ACustomer, AOrderList>> buffer;
    //<materialID, <producers, price lists>>
    using mapPriceLists = std::map<uint, std::pair<std::set<AProducer>, std::set<APriceList>>>;
    mapPriceLists dbsPriceLists;

    //thread stuff here
    std::mutex mtxBuffer;
    std::mutex mtxMapPriceLists;
    std::condition_variable cvFull;
    std::condition_variable cvEmpty;
    std::condition_variable cvMapNotAllProd;
};

//-------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__
int                main                                    ( void )
{

    using namespace std::placeholders;

    CWeldingCompany test;

    int numberOfThreads=24;

    //sscanf(arg[1],"%d",&numberOfThreads);
    AProducer array1[600];

    AProducerAsync array2[600];

    //array1[0] = make_shared<CProducerSync>(bind(&CWeldingCompany::AddPriceList, &test, _1, _2));

    //array2[0] = make_shared<CProducerAsync>(bind(&CWeldingCompany::AddPriceList, &test, _1, _2));

    //test.AddProducer(array1[0]);

    //test.AddProducer(array2[0]);

    //array2[0]->Start();


    for(int i=0;i<600;i++)

    {

        array1[i] = make_shared<CProducerSync>(bind(&CWeldingCompany::AddPriceList, &test, _1, _2));

        array2[i] = make_shared<CProducerAsync>(bind(&CWeldingCompany::AddPriceList, &test, _1, _2));

        test.AddProducer(array1[i]);

        test.AddProducer(array2[i]);

        array2[i]->Start();

    }


    test.AddCustomer(make_shared<CCustomerTest>(120));

    test.Start(numberOfThreads);

    test.Stop();


    //array2[0]->Stop();


    for(int i =0; i<600;i++)

        array2[i]->Stop();


    return 0;
}
#endif /* __PROGTEST__ */
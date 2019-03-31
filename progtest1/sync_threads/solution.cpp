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
        //todo delete duplicates before
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

    void Stop(void);

private:
    /*
     * This method implements customer threads.
     */
    void handleDemands(const ACustomer& customer)
    {
        AOrderList orderList;
        std::unique_lock<std::mutex> lockC(mtxBuffer);

        while((orderList = customer.get()->WaitForDemand()) != nullptr)
        {
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

            APriceList tmp = std::make_shared<CPriceList>(materialID);
            createPriceList(materialID, tmp);







            //pokud jsou oceneny vsechny objednavky z orderListu
//            orderList.first.get()->Completed();
        }
    }

    /*
     * This section asks producers for sending their price lists,
     * do so, if this thread hasn't received all lists by material ID from them yet.
     * Then, a thread waits until all producers will send their price lists.
     */
    void askProducers(const unsigned int& materialID)
    {
        std::unique_lock<std::mutex> lockMap(mtxMapPriceLists);
        bool contains = static_cast<bool>(dbsPriceLists.count(materialID)); // NOLINT
        bool complete = contains ? dbsPriceLists.at(materialID).first.size() == nProducers : false;

        if(!complete)
        {
            for(const auto& producer : producers)
                producer.get()->SendPriceList(materialID);
        }

        cvMapNotAllProd.wait(lockMap, [&complete] ()
        {
            return complete;
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
    using mapPriceLists = std::map<uint, std::pair<std::set<AProducer>, std::set<APriceList>>>;
    mapPriceLists dbsPriceLists;

    //thread stuff here
    std::mutex mtxBuffer;
    std::mutex mtxMapPriceLists;
    std::condition_variable cvFull;
    std::condition_variable cvEmpty;
    std::condition_variable cvMapNotAllProd;
};


//smazat
void bar(const APriceList& tmp)
{
    tmp.get()->Add(CProd(12,12,30));
    tmp.get()->Add(CProd(15,13,30));
    tmp.get()->Add(CProd(14,12,30));
    tmp.get()->Add(CProd(12,12,30));
}

//-------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__
int                main                                    ( void )
{
    using namespace std::placeholders;
    CWeldingCompany  test;

    APriceList tmp = std::make_shared<CPriceList>(12);
    bar(tmp);
    std::cout << tmp.get()->m_List.size() << std::endl;
    for(const auto& foo : tmp.get()->m_List)
    {
        std::cout << foo.m_W << std::endl;
    }

//  AProducer p1 = make_shared<CProducerSync> ( bind ( &CWeldingCompany::AddPriceList, &test, _1, _2 ) );
//  AProducerAsync p2 = make_shared<CProducerAsync> ( bind ( &CWeldingCompany::AddPriceList, &test, _1, _2 ) );
//  test . AddProducer ( p1 );
//  test . AddProducer ( p2 );
//  test . AddCustomer ( make_shared<CCustomerTest> ( 2 ) );
//  p2 -> Start ();
//  test . Start ( 3 );
//  test . Stop ();
//  p2 -> Stop ();
  return 0;
}
#endif /* __PROGTEST__ */

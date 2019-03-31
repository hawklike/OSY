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

// wrapper classes
//class CCustomerThreadWrapper
//{
//public:
//    explicit CCustomerThreadWrapper(unsigned int nCustomers) : nCustomerThreads(nCustomers) {}
//
//    void handleDemands()
//    {
//      AOrderList orderList;
//    }
//
//private:
//    unsigned int nCustomerThreads;
//    std::vector<std::thread> customerThreads;
//};
//
//class CProducerThreadWrapper
//{
//public:
//    explicit CProducerThreadWrapper(unsigned int nProducers) : nProducerThreads(nProducers) {}
//private:
//  unsigned int nProducerThreads;
//  std::vector<std::thread> producerThreads;
//
//};

class CWeldingCompany
{
public:
    static void SeqSolve(APriceList priceList, COrder& order);

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
    //thread serving for customers
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

    //working thread
    void evaluateOrders()
    {
        std::pair<ACustomer, AOrderList> order;
        std::unique_lock<std::mutex> lockP(mtxBuffer);

        while(!(buffer.empty() && finishedCustomers == nCustomers))
        {
            lockP.unlock();

            order = popBuffer();
            auto materialID = order.second.get()->m_MaterialID;

            lockP.lock();

            for(const auto& producer : producers)
                producer.get()->SendPriceList(materialID);

            cvFull.notify_one();

            //pokud jsou oceneny vsechny objednavky z orderListu
//            order.first.get()->Completed();
        }
    }

    //popping out an order from a buffer
    std::pair<ACustomer, AOrderList> popBuffer()
    {
        std::unique_lock<std::mutex> lockP(mtxBuffer);
        cvEmpty.wait(lockP, [this] ()
        {
            return !buffer.empty();
        });

        auto order = buffer.front();
        buffer.pop();
        lockP.unlock();

        return order;
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
};

//-------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__
int                main                                    ( void )
{
  using namespace std::placeholders;
  CWeldingCompany  test;

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

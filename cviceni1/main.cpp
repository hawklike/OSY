#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <chrono>

class CThreadManager
{
public:
    CThreadManager(uint32_t m, uint16_t n) : upperLimit(m), nThreads(n) {}

    void startThreads()
    {
        int remainder = upperLimit % nThreads;
        uint32_t unifDistribution = (upperLimit - remainder) / nThreads;
        uint32_t start = 0, end = 0;

        for(short i = 0; i < nThreads; i++)
        {
            if(remainder-- > 0) end = start + unifDistribution;
            else                end = start + unifDistribution - 1;

            threads.emplace_back(std::thread(&CThreadManager::sum, this, start, end));
            start = end + 1;
        }
    }

    void finishThreads()
    {
        for(auto &it : threads)
            if(it.joinable()) it.join();

        std::cout << "total: " << total << std::endl;
    }

    void referenceCount(uint32_t m) const
    {
        double total = 0;
        for(uint32_t i = 0; i < m; i++)
            total += (sqrt(i+1) + i) / sqrt(pow(i,2) + i + 1);

        std::cout << "referenced count: " << total << std::endl;
    }

private:
    void sum(const uint32_t start, const uint32_t end)
    {
        for(uint32_t i = start; i <= end; i++)
            total += (sqrt(i+1) + i) / sqrt(pow(i,2) + i + 1);
    }

    uint32_t upperLimit;
    uint16_t nThreads;
    double total = 0;
    std::vector<std::thread> threads;

};

void count(double& total, uint32_t start, uint32_t end)
{
    for(uint32_t i = start; i <= end; i++)
        total += (sqrt(i+1) + i) / sqrt(pow(i,2) + i + 1);
}

int main(int argc, const char* args[])
{
    uint32_t m = static_cast<uint32_t>(std::stoi(args[1]));
    uint16_t n = static_cast<uint16_t>(std::stoi(args[2]));

    CThreadManager sumCounter(m, n);
    sumCounter.startThreads();
    sumCounter.finishThreads();
    sumCounter.referenceCount(m);
    return 0;
}
#include <iostream>
#include <vector>
#include <thread>
#include <cmath>

class CThreadManager
{
public:
    CThreadManager(uint32_t m, uint16_t n) : m(m), n(n) {}

    void startThreads(const short nThreads)
    {
        double partition = static_cast<double>(m)/n;
        auto lowerPart = static_cast<uint32_t>(floor(partition));

        for(short i = 0; i < nThreads; i++)
        {
            uint32_t start, end;
            start = i == 0 ? 0 : i * lowerPart + 1;
            end = i == 0 ? lowerPart : start + lowerPart - 1;

            threads.emplace_back(std::thread(&CThreadManager::sum, this, std::ref(start), std::ref(end)));
        }
    }

    void finishThreads()
    {
        for(auto &it : threads)
            if(it.joinable()) it.join();

        std::cout << "total: " << total << std::endl;
    }

    void referenceCount(uint32_t m)
    {
        double total = 0;
        for(uint32_t i = 0; i < m; i++)
            total += (sqrt(i+1) + i) / sqrt(pow(i,2) + i + 1);

        std::cout << "referenced count: " << total << std::endl;
    }

private:
    void sum(const uint32_t &start, const uint32_t &end)
    {
        double tmp = 0;
        for(uint32_t i = start; i <= end; i++)
        {
            tmp += (sqrt(i+1) + i) / sqrt(pow(i,2) + i + 1);
        }

        std::cout << tmp << std::endl;
        total += tmp;
    }

    uint32_t m;
    uint16_t n;
    double total = 0;
    std::vector<std::thread> threads;

};

int main(int argc, const char* args[])
{
//    const short N_THREADS = 4;
    uint32_t m = static_cast<uint32_t>(std::stoi(args[1]));
    uint16_t n = static_cast<uint16_t>(std::stoi(args[2]));

    CThreadManager sumCounter(m, n);
    sumCounter.startThreads(n);
    sumCounter.finishThreads();
    sumCounter.referenceCount(m);

    return 0;
}
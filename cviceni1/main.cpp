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
        auto upperPart = static_cast<uint32_t>(ceil(partition));


        for(short i = 0; i < nThreads; i++)
        {
            uint32_t start, end;
            start = i * lowerPart + 1;
            end = i == 0 ? start + upperPart : start + lowerPart;

            threads.emplace_back(std::thread(&CThreadManager::sum, std::ref(start), std::ref(end)));

        }

    }

private:
    static void sum(const uint32_t &start, const uint32_t &end)
    {

    }

    uint32_t m;
    uint16_t n;
    std::vector<std::thread> threads;

};

int main(int argc, const char* args[])
{
//    const short N_THREADS = 4;
    uint32_t m = static_cast<uint32_t>(std::stoi(args[1]));
    uint16_t n = static_cast<uint16_t>(std::stoi(args[2]));

    CThreadManager sumCounter(m, n);
    sumCounter.startThreads(n);

//    std::cout << args[1] << " " << args[2] << std::endl;

    return 0;
}
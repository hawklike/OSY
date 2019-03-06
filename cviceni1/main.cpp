#include <iostream>
#include <vector>
#include <thread>

class CThreadManager
{
public:
    CThreadManager(uint32_t m, uint16_t n) : m(m), n(n) {}

    void solve(const std::vector<std::thread> &threads, int start, int end)
    {

    }


private:
    uint32_t m;
    uint16_t n;
    std::vector<std::thread> threads;

};

int main(int argc, const unsigned int args[])
{
    uint32_t m = args[0];
    uint16_t n = static_cast<uint16_t>(args[1]);

    CThreadManager sumCounter(m, n);

    return 0;
}
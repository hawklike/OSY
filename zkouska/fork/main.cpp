#include <iostream>
#include <zconf.h>
#include <mutex>
#include <thread>

using namespace std;

int g_X = 120;
mutex g_M[4];

void foo(int pos){
    lock_guard<mutex>l0 (g_M[pos % 4]);
    lock_guard<mutex>l1 (g_M[pos+1 % 4]);
    lock_guard<mutex>l2 (g_M[pos+2 % 4]);  //<---- zde by mělo nejspíš být pos+2, jinak mi to nedává smysl (zřejmě jde pouze o překlep)
    std::cout << g_X << std::endl;
    g_X+=pos;                               //   ^^ Nemyslim si, ze musi jit nutne o preklep. Pokud to uzamknu 2x stejnym mutexem, tak by podle me melo dojit k deadlocku.
}

int main()
{

    thread t1(foo, 9);
    thread t2(foo, 18);
    thread t3(foo, 21);

    t1.join();
    t2.join();
    t3.join();

    std::cout << g_X << std::endl;

}



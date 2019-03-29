/**************************************************************************
 - Main thread creates 2 working threads, which increment shared counter.
 - Shared counter is protected by mutex.
**************************************************************************/

#include <iostream>
#include <vector> 
#include <chrono>
#include <thread>
#include <mutex>                                                          

using namespace std;

#define NUMBER_OF_THREADS 2

//-------------------------------------------
class CounterClass  
{
private:
  unsigned long long c;
  mutex mtx;

public: 
  CounterClass()
  {
    c = 0;
  }

  void adding(int tid, int value)
  {
    for ( int i = 1; i <= value; i++ ) 
    {
      lock_guard<std::mutex> lock(mtx);
      //mtx.lock();
      c = c + i;
      //mtx.unlock();
    }
  }

  unsigned long long getSum()
  {
    return c;
  }
};


//-------------------------------------------
int main ( int argc, char * argv [] )
{
  CounterClass    counterObj;    
  vector<thread>  threads;
  int             values[NUMBER_OF_THREADS];

  // Check arguments
  if ( argc != 3 || 
       sscanf(argv[1], "%d", &values[0]) != 1 ||
       sscanf(argv[2], "%d", &values[1]) != 1   )
  {
    printf("Usage: %s integer_1 integer_2\n", argv[0]);
    return 1;
  }
  
  // Create threads
  for ( int i = 0; i < NUMBER_OF_THREADS; i++ )
  {
    printf("Main:     Creating thread %d\n", i);
    threads.push_back( thread(&CounterClass::adding, &counterObj, i, values[i]) ); 
  }

  // Wait for threads
  for ( int i = 0; i < NUMBER_OF_THREADS; i++ )
  {
    printf("Main:     Joining thread %d\n", i);
    threads[i].join();
  }
      
  // Check result
  printf("Main:     Counter equals to        %llu\n", counterObj.getSum() );

  unsigned long long c = 0;
  
  for ( int i = 0; i < NUMBER_OF_THREADS; i++) 
  {
    for ( int j = 1; j <= values[i]; j++ ) 
    {
      c = c + j;
    }    
  } 

  printf("Main:     Counter should equals to %llu\n", c);                                    

  printf("Main:     Stop\n");
  return 0;
}


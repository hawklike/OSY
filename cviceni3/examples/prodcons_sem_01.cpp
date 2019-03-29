/********************************************************************************
  - Producer/consumer problem synchronized by semaphores.
  - There are 2 errors in the code. => Try to find then. 
*********************************************************************************/

#include <iostream>
#include <vector>
#include <chrono>
#include <deque>
#include <thread>
#include <mutex>
#include <semaphore.h>

#define BUFFER_SIZE 5

using namespace std;

struct item_t
{
  int  tid;
  int  id;
  int  value;
};

/*************************************/
class BufferClass
{
/****************************/
private:
  deque<item_t*>       buff;
  mutex                mtx; 
  sem_t                sem_full, sem_free;
  
  /****************************/
  void PrintBuffer()
  {
    printf("Buffer: ");
    for (deque<item_t*>::iterator it = buff.begin(); it!=buff.end(); ++it)
      printf("[%d, %d, %d] ",(*it)->tid, (*it)->id, (*it)->value);
    printf("\n");
  }

/****************************/
public: 
  BufferClass() 
  { 
    sem_init ( &sem_free, 0, 0 );                      
    sem_init ( &sem_full, 0, BUFFER_SIZE );                                
  }

  ~BufferClass()
  { 
      sem_destroy ( &sem_free );
      sem_destroy ( &sem_full );  
  }
 
  /****************************/
  virtual void insert(item_t *item) 
  {
    unique_lock<mutex> ul (mtx);
    sem_wait( &sem_free );
    
    buff.push_back(item);
    
    printf("Producer %d:  item [%d,%d,%d] was inserted\n", item->tid, item->tid, item->id, item->value);

    PrintBuffer();

    sem_post( &sem_full );
  }

  /****************************/
  virtual item_t * remove(int tid) 
  {
    item_t *item;

    sem_wait( &sem_full );
    unique_lock<mutex> ul (mtx);
    item = buff.front();
    buff.pop_front();

    printf("Consumer %d:  item [%d,%d,%d] was removed\n", tid, item->tid, item->id, item->value);
   
    PrintBuffer();
   
    sem_post( &sem_free );
    return item;
  }
  
  /****************************/
  virtual bool empty()
  {
    return buff.empty();
  }
};

/*************************************/
void producer(int tid, BufferClass &buff)
{
  int count = 0;

  for ( int i = 0; ; i++ )
  {
    item_t *item  = new item_t { tid, count, rand() % 100 };
    count++;
    
    buff.insert(item);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}

/*************************************/
void consumer(int tid, BufferClass &buff )
{
  for ( int i = 0; ; i++ ) 
  {
    item_t * item  = buff.remove(tid);
    delete(item);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

/*************************************/
int main ( int argc, char * argv [] )
{
  int            prod, cons;
  BufferClass    buffer;
  vector<thread> threads;

  // Check arguments
  if ( argc != 3 || sscanf ( argv[1], "%d", &prod ) != 1
                 || sscanf ( argv[2], "%d", &cons ) != 1
                 || prod < 1 || cons < 1 )
    {
      printf ( "Usage: %s <prod> <cons>\n", argv[0] );
      return ( 1 );
    }
  
  for ( int i = 0; i < prod; i ++ )
    threads.push_back ( thread ( producer, i, ref(buffer) ) );

  for ( int i = 0; i < cons; i ++ )
    threads.push_back ( thread ( consumer, i, ref(buffer) ) );

  for ( auto & t : threads )
    t.join (); 

  return 0;
} 

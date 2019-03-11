/* reseni s C++ vlakny a mutexy, odstranena vetsina globalnich promennych
 * misto zamykani (mutexy) se pouzivaji atomicke operace z knihovny C++11
 * (template<typename _T> atomic) a jejich specializace atomic_int
 */
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <vector>
#include <thread>
#include <atomic>
using namespace std;

/* Test prvociselnosti - naivni.
 */
int isPrime ( int x )
{
  int max, i;

  if ( x < 2 ) 
    return 0;
  max = (int)sqrt ( x );
  for ( i = 2; i <= max; i ++ )
    if ( x % i == 0 )
      return 0;
  return 1;
}

/* Funkce vlakna - vezme dalsi cislo k otestovani, otestuje,
 * upravi pocitadlo.
 */
void thrFunc ( int max, volatile atomic_int & pos, volatile atomic_int & cnt )
{
  int localCnt = 0;
  while ( 1 )
  {
    int x = pos ++; 
    // operace ++ je atomicka na atomic_int
    
    if ( x >= max ) 
      break;
    if ( isPrime ( x ) ) 
      localCnt ++;
  }
  // atomicke pricteni
  cnt . fetch_add ( localCnt );
}

int main ( int argc, char * argv [] )
{
  int              thr, max;
  atomic_int       pos ( 0 ), cnt ( 0 );
  vector<thread>   threads;

  if ( argc != 3 
       || sscanf ( argv[1], "%d", &max ) != 1 
       || sscanf ( argv[2], "%d", &thr ) != 1 )
  {
    printf ( "Usage: %s <max> <thr>\n", argv[0] );
    return 1;
  }

  /* Vytvoreni vlaken - vlakno dostane svoji identifikaci (cele cislo).
   * chceme predat reference na lokalni promenne, predame je v podobe wrapperu ref
   * (bez nej by se hodnoty predaly hodnotou, to nechceme, navic to ani nejde (atomic 
   * typy nejsou kopirovatelne ani presouvatelne) 
   */
  for ( int i = 0; i < thr; i ++ )
    threads . push_back ( thread ( thrFunc, max, ref ( pos ), ref ( cnt ) ) );

  for ( auto & t : threads )
    t . join ();

  printf ( "Prvocisel < %d je %d\n", max, cnt . load () );
  return 0;
}

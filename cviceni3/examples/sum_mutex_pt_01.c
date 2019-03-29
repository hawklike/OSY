/**************************************************************************
 - Main thread creates 2 working threads, which increment shared counter.
 - Shared counter is protected by mutex.
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUMBER_OF_THREADS 2

long int          g_cnt = 0;
pthread_mutex_t   g_mtx;

struct thread_data
{
  int  thread_id;
  int  value;
};

/* ------------------------------------------- */
void * workingThread ( void * threadarg )
{
  int i;
  struct thread_data *my_data;
  my_data = (struct thread_data *) threadarg;

  for ( i = 1; i <= my_data->value; i++ ) 
  {
    pthread_mutex_lock( &g_mtx );
    g_cnt = g_cnt + i;
    pthread_mutex_unlock( &g_mtx );
  }
  
  return NULL;
}

/* ------------------------------------------- */
int main(int argc, char *argv[])
{
  pthread_attr_t       attr;
  struct thread_data   thread_data_array[NUMBER_OF_THREADS];
  pthread_t            threads[NUMBER_OF_THREADS];
  int                  rc, i, j;

  /* Check arguments */
  if ( argc != 3 || 
       sscanf(argv[1], "%d", &thread_data_array[0].value) != 1 ||
       sscanf(argv[2], "%d", &thread_data_array[1].value) != 1    )
  {
    printf("Usage: %s integer_1 interger_2\n", argv[0]);
    return 1;
  }

  printf("Main:     Counter = %ld\n", g_cnt);

  /* Setup mutex */
  pthread_mutex_init( &g_mtx, NULL );

  /* Setup thread attributes */
  pthread_attr_init(&attr);                                                 
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);   

  for( i = 0; i < NUMBER_OF_THREADS; i++) 
  {
    /* Initialize thread arguments */
    thread_data_array[i].thread_id = i;

    /* Create threads */
    printf("Main:     Creating thread %d\n", i);
    rc = pthread_create(&threads[i], &attr, workingThread, (void *) &thread_data_array[i]);
    if (rc) 
    {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      return EXIT_FAILURE;
    }
  }

  /* Realse thread attributes */
  pthread_attr_destroy(&attr);                                                    

  /* Wait for threads */
  for ( i = 0; i < NUMBER_OF_THREADS; i++) 
  {
    printf("Main:     Joining thread %d\n", i);
    rc = pthread_join(threads[i], NULL);
    if (rc) 
    {
      printf("ERROR return code from pthread_join() is %d\n", rc);
      return EXIT_FAILURE;
    }
  }

  /* Free mutex */
  pthread_mutex_destroy ( &g_mtx );

  /* Check result */
  printf("Main:     Counter equals to        %ld\n", g_cnt);

  g_cnt = 0;
  
  for ( i = 0; i < NUMBER_OF_THREADS; i++) 
  {
    for ( j = 1; j <= thread_data_array[i].value; j++ ) 
    {
      g_cnt = g_cnt + j;
    }    
  } 

  printf("Main:     Counter should equals to %ld\n", g_cnt);

  printf("Main:     Stop\n");
  return 0;
}


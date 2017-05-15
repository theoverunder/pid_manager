#include "pid.h"

static const int NUM_THREADS = 100;
pthread_mutex_t mutex;



void *assignPids(void *params)
{
    
    pthread_mutex_lock(&mutex);
    pid_t tempProcessId;
    int pidGiven;
    
    tempProcessId = pthread_self();
    pidGiven = allocate_pid(tempProcessId);
    pthread_mutex_unlock(&mutex);
    if ( pidGiven > -1)
    {
        printf("PID ASSIGNED IS %d\n", pidGiven);
    }
    else 
    {
        printf("Error assigning PID\n");
        return;
    }
    
    sleep(rand() % 7);
    
    release_pid(pidGiven);
    printf("Released PID %d\n " ,pidGiven);
}


int main(void)
{
    pthread_attr_t thread_attributes;
    
    pthread_t threads[NUM_THREADS];
    int i;
   
    pthread_mutex_init(&mutex, NULL);
    srand((unsigned)time(NULL));
    
    if(allocate_map() != 0)
    {
        printf("Failed to create map\n");
        return 1;
    }
    
    pthread_attr_init(&thread_attributes);
    for (i = 1; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], &thread_attributes, assignPids, NULL);
      // pthread_join(threads[i], NULL);
    }
    
    for (i = 1; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
        
    }
    
    return 0;
}
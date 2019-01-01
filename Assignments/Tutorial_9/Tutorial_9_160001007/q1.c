
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <semaphore.h> 

  
sem_t semaphore; 
int val=0;

void* thread1(void* arg) { 
    sem_wait(&semaphore); 
    val+=1;
    sem_post(&semaphore); 
} 
void* thread2(void* arg) { 
    sem_wait(&semaphore); 
    val-=1;
    sem_post(&semaphore); 
} 
  
  
int main() { 
    sem_init(&semaphore, 0, 1); 
    pthread_t t1,t2; 

    pthread_create(&t1,NULL,thread1,NULL);  
    pthread_create(&t2,NULL,thread2,NULL); 
    pthread_join(t1,NULL); 
    pthread_join(t2,NULL); 
    printf("%d\n",val);
    sem_destroy(&semaphore); 
    return 0; 
} 

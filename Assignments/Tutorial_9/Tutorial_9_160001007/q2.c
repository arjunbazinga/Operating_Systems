#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


sem_t empty, full, array_access;

int BUFFER_SIZE = 10;
int buffr[10];

int l = 0;
int r = 0;

void *producer(){
    int next_produced=0;
    while(1){
        next_produced++;
        sem_wait(&empty); 
        sem_wait(&array_access);
        buffr[l]=next_produced;
        l = (l + 1) % BUFFER_SIZE;
        sem_post(&array_access);
        sem_post(&full);
    }
}

void *consumer(){
    int next_consumed;
    while(1){
        sem_wait(&full); 
        sem_wait(&array_access);
        next_consumed=buffr[r];
        r = (r + 1) % BUFFER_SIZE;
        sem_post(&array_access);
        sem_post(&empty);
        printf("Consumed %d\n",next_consumed);
    } 
}

int main(){
 
    sem_init(&array_access, 0, 1);
    sem_init(&full, 0, 0); 
    sem_init(&empty, 0, BUFFER_SIZE);    
    pthread_t th1,th2;

    pthread_create( &th1, NULL, producer, NULL);
    pthread_create( &th2, NULL, consumer, NULL);

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    sem_destroy(&array_access); 
    
    return 0;    
}


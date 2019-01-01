#include <stdlib.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <unistd.h> 

sem_t br,cr,sr;
int seats=10;

void *barber(void* x) { 
    while(1){
        sem_wait(&cr);
        sem_wait(&sr);
        seats++;
        int s=seats;
        printf("Barber cut hair at seat:%d\n", s);
        sem_post(&br);
        sem_post(&sr);
    }
    return NULL; 
}

void *customer(void* x) { 
    while(1){
        sem_wait(&sr);
        if(seats>0){
            int temp=seats;
            printf("Customer:%d waiting at seat %d \n", *((int*)x), temp);
            seats--;
            sem_post(&cr);
            sem_post(&sr);
            sem_wait(&br);
            pthread_exit(0);
        }
        else{
            sem_post(&sr);
        } 
    }
    return NULL; 
} 
int vals[101];

int main() { 
    sem_init(&br,0,0);
    sem_init(&cr,0,0);
    sem_init(&sr,0,1);    
    pthread_t thread_id[500]; 
    int temp=0;
    pthread_create(&thread_id[0], NULL, barber, (void *)&temp); 
    for(int i=1;i<=100;i++){
        vals[i]=i;
        pthread_create(&thread_id[i], NULL, customer, (void *)(vals+i)); 
        
    }
    for(int i=1;i<=100;i++){
        pthread_join(thread_id[i],NULL);
    }
}
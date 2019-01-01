#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;

void* study_os(){
    printf("Study OS \n");
    sem_post(&semaphore);
}

void* drink_coffee(){    
    printf("Drink Coffee \n");
    sem_post(&semaphore);
}

void* take_exam(){
    sem_wait(&semaphore);
    printf("Take Exam \n");
}

int main(){

    sem_init(&semaphore, 0, -1);
    
    pthread_t th1,th2,th3;
    
    pthread_create( &th2, NULL, drink_coffee, NULL);
    pthread_create( &th1, NULL, study_os, NULL);
    pthread_create( &th3, NULL, take_exam, NULL);

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    pthread_join(th3,NULL);

    return 0;    
}


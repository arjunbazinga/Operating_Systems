#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t a, b;

void *A(){
  while (1){
    sem_wait(&a);
    printf("A");
    sem_post(&b);
  }
}

void *B(){
  while (1){
    sem_wait(&b);
    printf("B");
    sem_post(&a);
  }
}

int main(){
  sem_init(&a, 0, 1);
  sem_init(&b, 0, 0);

  pthread_t th1, th2;

  pthread_create(&th2, NULL, B, NULL);
  pthread_create(&th1, NULL, A, NULL);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  return 0;
}

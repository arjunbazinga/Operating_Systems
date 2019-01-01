// Write a program in which four threads of a
// process are accessing the same variable.

// Each of the thread is modifying the variable in
// different manner.
// by using synchronization
// (i.e. mutex) to ensure the correct execution.
// By Arjun Srivastava

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int a = 1;
pthread_mutex_t mutexa;

void proc1(){
    pthread_mutex_lock(&mutexa);
    a = a + 10; 
    pthread_mutex_unlock(&mutexa);
}

void proc2(){
    pthread_mutex_lock(&mutexa);
    a = a + 20;
    pthread_mutex_unlock(&mutexa);
}

void proc3(){
    pthread_mutex_lock(&mutexa);
    a =  a - 20;
    pthread_mutex_unlock(&mutexa);
}

void proc4(){
    pthread_mutex_lock(&mutexa);
    a = a - 10;
    pthread_mutex_unlock(&mutexa);
}

int main(){
  pthread_t thrdID[4];
  if (pthread_mutex_init (&mutexa, NULL)){
      printf("Mutex init failed\n");
      return 1;
  }
  
  pthread_create(&thrdID[0], NULL, (void *)proc1, NULL);
  pthread_create(&thrdID[1], NULL, (void *)proc2, NULL);
  pthread_create(&thrdID[2], NULL, (void *)proc3, NULL);
  pthread_create(&thrdID[3], NULL, (void *)proc4, NULL);
  pthread_join(thrdID[0], NULL);
  pthread_join(thrdID[1], NULL);
  pthread_join(thrdID[2], NULL);
  pthread_join(thrdID[3], NULL);

  printf("%d\n", a);
  pthread_mutex_destroy(&mutexa);
  return 0;
}
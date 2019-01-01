// Write a program in which four threads of a
// process are accessing the same variable.

// Each of the thread is modifying the variable in
// different manner. Display output of each the
// thread and check. (Correct or not)

// By Arjun Srivastava

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int a = 1;

void proc1(){
    a = 10 + a;
}

void proc2(){
    a = 20 + a;
}
void proc3(){
    a = a - 20;
}

void proc4(){
    a = a - 10;
}

int main(int argc, char **argv){
  pthread_t thrdID;
  pthread_create(&thrdID, NULL, (void *)proc1, argv[1]);
  pthread_create(&thrdID, NULL, (void *)proc2, argv[1]);
  pthread_create(&thrdID, NULL, (void *)proc3, argv[1]);
  pthread_create(&thrdID, NULL, (void *)proc4, argv[1]);
  printf("%d\n", a);
  pthread_join(thrdID, NULL);
  return 0;
}
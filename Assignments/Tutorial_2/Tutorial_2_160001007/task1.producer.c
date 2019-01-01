#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>



int main(){
  int size = 256;
  key_t key = ftok("password", 42);
  int seg_id = shmget(key, size, IPC_CREAT|0666);
  char* mem = (char*) shmat(seg_id, NULL, 0);
  scanf("%s", mem);
  shmdt(mem);
  return 0;
}
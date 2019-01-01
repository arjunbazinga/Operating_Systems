#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>



int main(){
  
  int size = 256;
  key_t key = ftok("password", 42);
  int seg_id = shmget(key, size, 0666);
  char* mem = (char*) shmat(seg_id, NULL, 0);
  printf("%s\n", mem);
  shmdt(mem);
  shmctl(seg_id,IPC_RMID, 0);
  return 0;
}
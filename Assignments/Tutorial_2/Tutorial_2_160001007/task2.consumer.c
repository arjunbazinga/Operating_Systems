#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>



int main(){
  int i;
  int size = 256;
  key_t key = ftok("password", 42);
  int seg_id = shmget(key, size, IPC_CREAT|0666);
  int* mem = (int*) shmat(seg_id, NULL, 0);
  scanf("%d", &i);
  printf("%d\n", mem[i-1]);
  
  shmdt(mem);
  shmctl(seg_id,IPC_RMID, 0);
  return 0;


}
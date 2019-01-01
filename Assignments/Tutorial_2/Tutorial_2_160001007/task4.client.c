#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>



int main(){
  int size = sizeof(int)*4;
  key_t key = ftok("password", 42);
  int seg_id = shmget(key, size, IPC_CREAT|0666);
  int* mem = (int*) shmat(seg_id, NULL, 0);
  int ans = 0;
  for(int i= 0; i<4 ;i++){
    ans += mem[i];
  }
  printf("%d\n", ans);
  shmdt(mem);
  shmctl(seg_id,IPC_RMID, 0);
  return 0;


}
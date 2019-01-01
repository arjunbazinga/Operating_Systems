#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>



int main(){
  int size = sizeof(int)*5;
  int seg_id = shmget(IPC_PRIVATE, size, IPC_CREAT|0666);
  pid_t id = fork();
  if (id==0){
    int* mem = (int*) shmat(seg_id, NULL, 0);
    int ans = 0;
    while(mem[4] !=11){
      ;
    }
    for(int i= 0; i<4 ;i++){
      ans += mem[i];
    }
    printf("%d\n", ans);
    shmdt(mem);
    shmctl(seg_id,IPC_RMID, 0);
  }
  else{
    int* mem = (int*) shmat(seg_id, NULL, 0);
    for(int i= 0; i<4 ;i++){
      scanf("%d",mem+i);
    }
    mem[4] = 11;
    shmdt(mem);
    return 0;
    wait(NULL);
  }


}

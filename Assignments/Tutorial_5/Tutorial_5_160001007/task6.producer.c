#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>


#define BUFFER_SIZE 10

typedef struct {
    char q[BUFFER_SIZE];
    int start, end;
} buffer;

int is_empty(buffer* data){
  return data->start == -1 &&  data->end == -1;
}

int is_full(buffer* data){
 return  (data->start == data->end) && data->end == -1 ;
}

void append(buffer* data, char x){
  data->q[data->end] = x;
  data->end = (data->end + 1) % BUFFER_SIZE;
}

char pop(buffer* data){
  char ans = data->q[data->start];
  data->start = (data->start + 1) % BUFFER_SIZE;
  if (data->start == data->end){
     data->start = -1;
    data->end = -1;
  }
   
  return ans;
}

int main(){
  key_t key = ftok("password", 42);
  int seg_id = shmget(key, sizeof(buffer), IPC_CREAT|0666);
  buffer* data = (buffer*) shmat(seg_id, NULL, 0);

  data->start = -1;
  data->end = -1;
  while(!is_full(data)){
    append(data, 'a'+ rand()%26);
    sleep(2);
  }

  shmdt(data);
  return 0;
}
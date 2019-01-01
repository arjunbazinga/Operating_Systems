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
  return data->start == data->end;
}

int is_full(buffer* data){
 return  (data->end + 1 )% BUFFER_SIZE == data->start ;
}

void append(buffer* data, char x){
  data->q[data->end] = x;
  data->end = (data->end + 1) % BUFFER_SIZE;
}

char pop(buffer* data){
  char ans = data->q[data->start];
  data->start = (data->start + 1) % BUFFER_SIZE;
  return ans;
}

int main(){
  key_t key = ftok("password", 42);
  int seg_id = shmget(key, sizeof(buffer), IPC_CREAT|0666);
  buffer* data = (buffer*) shmat(seg_id, NULL, 0);

  data->start = 0;
  data->end = 0;
  while(!is_full(data)){
    append(data, 'a'+ rand()%26);
    sleep(2);
  }

  shmdt(data);
  return 0;
}
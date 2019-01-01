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
  int* mem = (int*) shmat(seg_id, NULL, 0);
   int n = size;
   int i = 3, count, c;

   for ( count = 2 ; count <= n ;  )
   {
      for ( c = 2 ; c <= i - 1 ; c++ )
      {
         if ( i%c == 0 )
            break;
      }
      if ( c == i )
      {
         mem[count-1] = i;
         count++;
      }
      i++;
   }         
  shmdt(mem);
  return 0;
}
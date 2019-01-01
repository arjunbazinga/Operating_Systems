#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 10000

int upto = 2;
int ans[MAX];


void fib(){
  ans[1] = 0;
  ans[2] = 1;
  while (upto<MAX){
    ans[upto+1]  = ans[upto] + ans[upto-1];
    upto++;
  }
}




int main(int argc, char **argv){
  pthread_t thrdID;
  pthread_create(&thrdID, NULL, (void *)fib, NULL);
  int n ;
  scanf("%d", &n);
  while(n>upto) {;}
  for(int i=1; i<n;i++)
  printf("fib %d: %d\n",i, ans[i]);
  return 0;
}
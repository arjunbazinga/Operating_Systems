#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/wait.h>

int main(){
    key_t k=ftok("password", 1);
    key_t kb=ftok("password", 2);
    key_t kc=ftok("password", 3);

    int s3=shmget(kc,4*sizeof(int),IPC_CREAT|0666);
    int s1=shmget(k,5*sizeof(float),IPC_CREAT|0666);
    int s2=shmget(kb,5*sizeof(int),IPC_CREAT|0666);

    float *a=(float*)shmat(s1,NULL,0);
    int *b=(int*)shmat(s2,NULL,0);
    int *c=(int*)shmat(s3,NULL,0);
    float tmp;

    printf("Started Client 2\n");

    while(1){
        if(!b[1]){
            tmp=(3*a[1]+2*a[4])/5;
            if(tmp!=a[1] || abs(tmp-a[1])>0.001){
                a[1]=tmp;
                b[1]=1;
            }
            else{
                b[1]=1;
                c[1]=1;
                break;
            }
        }
    }
    printf("Client 2 temp: %f\n",a[1]);
    return 0;
}
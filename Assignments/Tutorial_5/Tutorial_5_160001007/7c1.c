#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/wait.h>

int main(){
    key_t k = ftok("password",1);
    key_t kb = ftok("password",2);
    key_t kc = ftok("password",3);

    int s3 = shmget(kc,4*sizeof(int),IPC_CREAT|0666);
    int s1 = shmget(k,5*sizeof(float),IPC_CREAT|0666);
    int s2 = shmget(kb,5*sizeof(int),IPC_CREAT|0666);

    float *a = (float*)shmat(s1,NULL,0);
    int *b = (int*)shmat(s2,NULL,0);
    int *c = (int*)shmat(s3,NULL,0);
    float tmp;

    printf("Started Client 1\n");


    while(1){
        if(!b[0]){
            tmp = (3*a[0]+2*a[4])/5;
            if(tmp != a[0] || abs(tmp-a[0]) > 0.001){
                a[0] = tmp;
                b[0] = 1;
            }
            else{
                b[0] = 1;
                c[0] = 1;
                break;
            }
        }
    }
    printf("Client 1 temp: %f\n",a[0]);
    return 0;
}
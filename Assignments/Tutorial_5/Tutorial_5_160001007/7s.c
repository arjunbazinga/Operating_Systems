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
    int i=0;
    for(i=0;i<4;i++) 
        c[i]=0;
    for(i=0;i<5;i++) 
        a[i]=rand()%10+1;
    for(i=0;i<4;i++) 
        b[i]=0;

    printf("Started Server\n");

    while(1){
        if(c[0]&&c[1]&&c[2]&&c[3]) break;
        if(b[0]&&b[1]&&b[2]&&b[3]){
            a[4]=(2*a[4]+a[0]+a[1]+a[2]+a[3])/6;
            for(i=0;i<4;i++){
                if(!c[i])
                    b[i]=0;
            }
        }
    }
    printf("Central temp: %f\n",a[4]);
    return 0;
}
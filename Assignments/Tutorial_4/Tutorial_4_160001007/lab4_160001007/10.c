#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<time.h>


int main(){
    int fd[3],pip[2];
    fd[0]=open("c1.txt",O_RDONLY); 
    fd[1]=open("c2.txt",O_RDONLY);
    fd[2]=open("c3.txt",O_RDONLY);
    int wf=open("write10.txt" ,O_CREAT | O_WRONLY, 0666);

    int s = 50;
    char ans[3*s];
    char* buff = ans;

    for(int i=0;i<3;i++){
       pipe(pip);
       if(fork() == 0){
           close(pip[0]);
           char temp[s];
           sleep(3 + (rand())%8);
           read(fd[i],temp, s);
           write(pip[1],temp, s);
           exit(0);

       }else{
           close(pip[1]);
           read(pip[0],buff,s);
           while(wait(NULL)>0);
           buff += s;
       }
    }
    write(wf, ans ,3*s);
    return 0;
        
}
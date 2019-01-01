#include<bits/stdc++.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>


using namespace std;

int main(){
    int fd = open("text.txt",O_RDONLY,S_IRUSR);
    int fd2 = open("write4.txt",O_CREAT | O_RDWR,S_IRUSR | S_IWUSR);
    auto s = 100;
    char buff[s];
    int n = s;
    while(n){
        n=read(fd,buff,sizeof(buff));
        write(fd2,buff,n);
    }
    close(fd);
    close(fd2);
    return 0;   
}
#include<bits/stdc++.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>


using namespace std;

int main(){
    int fd1 = open("text.txt",O_RDONLY);
    int fd2 = open("write9.txt",O_RDWR| O_CREAT,S_IRUSR | S_IWUSR);
    dup2(fd1,0);
    dup2(fd2,1);
    char buff;
    auto s = sizeof(buff);
    auto n = 1;
    while(n){
        write(1, &buff, s);
        n=read(0, &buff, s);
    }
    close(fd1);
    close(fd2);
    return 0;
}
#include<bits/stdc++.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>


using namespace std;

int main(){
    int fd1 = open("text.txt",O_RDONLY);
    int fd2 = open("write8.txt",O_RDWR| O_CREAT,S_IRUSR | S_IWUSR);
    close(0);
    close(1);
    dup(fd1);
    dup(fd2);
    char buff;
    auto s = sizeof(buff);
    auto n = 1;
    while(n){
        n = read(0, &buff, s);
        write(1, &buff, s);
        
    }
    close(fd1);
    close(fd2);
    return 0;
}
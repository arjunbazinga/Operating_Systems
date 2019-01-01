#include<bits/stdc++.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>


using namespace std;

int main(){
    auto fd= open("text.txt",O_RDONLY,S_IRUSR);
    char buff;
    auto s = sizeof(buff);
    auto n = lseek(fd,-1,SEEK_END);
    while(n != -1){
        read(fd, &buff, s);
        write(1, &buff, s);
        n=lseek(fd, -2, SEEK_CUR);
    }
    close(fd);
    return 0;   
}
#include<bits/stdc++.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>


using namespace std;

int main(){
    int fd= open("text.txt",O_RDONLY,S_IRUSR);
    char buff;
    auto s = sizeof(buff);
    auto n = 1;
    while(n){
        n=read(fd,&buff,s);
        write(1,&buff,s);
    }
    close(fd);
    return 0;

}
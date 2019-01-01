#include<bits/stdc++.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>


using namespace std;

int main(){
    auto fd = open("text.txt",O_RDONLY,S_IRUSR);
    auto fd2 = open("write3.txt",O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    char buff;
    auto s = sizeof(buff);
    auto n = 1;
    while(n){
        n = read(fd,&buff,s);
        write(fd2,&buff,s);
       
    }
    close(fd);
    close(fd2);
    return 0;

}
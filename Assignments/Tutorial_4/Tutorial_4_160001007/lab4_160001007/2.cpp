#include<bits/stdc++.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>


using namespace std;

int main(){
    int fd= open("text.txt",O_RDONLY,S_IRUSR);
    auto s = 100;
    char buff[s];
    auto n=s;
    while(n){
        n=read(fd,buff,s);
        write(1,buff,n);
    }
    close(fd);
    return 0;
    
}
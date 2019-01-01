
#include<bits/stdc++.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>

using namespace std;

int main(){
    int s = 50;
    char ans[s];

    if (fork()==0){
       auto blah = mkfifo("/tmp/fifo",S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
       auto f = open("/tmp/fifo", O_WRONLY);
       read(0,ans, s);
       write(f,ans, s);
       close(f);
       exit(0);
    }
    else {
       auto blah = mkfifo("/tmp/fifo",S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
       auto f = open("/tmp/fifo", O_RDONLY);
       read(f,ans,s);
       int n = atoi(ans);
       int t = 1;
       for (int i=2; i <= n; i++){
           t *= i;
       }
       cout << t<< endl;
       close(f);

       
    }
    return 0;
        
}
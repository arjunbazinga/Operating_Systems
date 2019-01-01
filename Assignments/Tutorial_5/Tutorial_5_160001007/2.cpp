

#include<bits/stdc++.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>

using namespace std;

int main(){
    int pip[2];
    int s = 50;
    char ans[s];
    pipe(pip);
    if (fork()){
       close(pip[0]);
       read(0,ans, s);
       dup2(pip[1],1);
       write(1,ans, s);
       while(wait(NULL)>0);
    }
    else {
    
       close(pip[1]);
       dup2(pip[0],0);
       read(0,ans,s);
       cout << ans;
       exit(0);
    }
    return 0;
        
}
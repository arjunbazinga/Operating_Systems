#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>


int main(){
  int a  = 1;
  pid_t id = fork();
  if (id == -1 ){
    printf("Boohoo, coudn't fork\n");
  }
  else {
    if (id == 0){
      printf("Child : Hello from the child processs\n");
      printf("Child : Hey my parent's id is : %d\n", getppid()); // quesiton 5
      printf("Child : changing value of a to 10 \n"); // question number 4
      a = 10;
      printf("Child: Value of a is : %d\n", a);
      execlp("firefox", "firefox", NULL); // question 2 
    }
    else {
        printf("Parent : hello from the parent\n");
        printf("Parent : my id is %d\n", getpid()); //question 5
        printf("Parent : changing value of a to 20 \n");
        a = 20;
        printf("Parent : Value of a is : %d\n", a);
        printf("Parent : forking again!\n ");
                pid_t id2 = fork(); //  Forking second time class example question 1
                if (id2 == -1){
                  printf("Boohoo couldn't fork the second time\n");
                }
                else {
                  if (id2 == 0){
                    printf("PC: Forked the second time: message from the child\n");
                    printf("PC: Running gedit in this child:\n ");
                    execlp("gedit", "gedit", NULL); //question 2
                  }
                  else {
                    printf("pp: Speaking from the parent parent here\n");
      
                  }
                }
        printf("Parent:  waiting for my children to die \n");



        wait(NULL); // calling wait question 6
    }

  }
}
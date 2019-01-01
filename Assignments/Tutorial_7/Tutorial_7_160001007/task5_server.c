#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <wait.h>

int main(){
  int socket_desc = socket(AF_INET , SOCK_STREAM , 0);

  struct sockaddr_in server;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_family = AF_INET;
  server.sin_port = htons( 8080 );
  
  int status = bind(socket_desc,(struct sockaddr *)&server , sizeof(server));
  if (status == -1){
    printf("Server: Couldn't bind server\n");
    return 1;
  }
  else{
    printf("Server: Bound server\n");
    int c = sizeof(struct sockaddr_in);
    int num_clients = 2;
    listen(socket_desc , num_clients);
    struct sockaddr_in clients[num_clients];
    int sockets[num_clients];
    for (int i = 0; i< num_clients; i++){
       sockets[i] = accept(socket_desc, (struct sockaddr *)&clients[i], (socklen_t*)&c);
       if (sockets[i] == -1){
          printf("Server: couldn't accept connection\n");
       }
       else{
          printf("Server: Accepted connection\n");
          char message[] = "Server Response: You have connected Successfully.\n";
          write(sockets[i] , message , strlen(message));
        }
    }
    int len_replies = 100;
    char replies[len_replies];
    for (int i=0; i < num_clients; i++){
      pid_t p = fork();
      
      if (p==-1){
        printf("couldn't fork, couldn't create listeners\n ");
      }
      else{
        if (p==0){
          while(1){
            recv(sockets[i], replies, len_replies, 0);
            printf("Client %d says %s", i, replies );
            for (int j=0; j<num_clients; j++){
              if (j != i)  {
                send(sockets[j], replies, len_replies, 0);
              }
            }
          }
        }
      }
    }
   
    close(socket_desc);
  }
  wait(NULL);

}
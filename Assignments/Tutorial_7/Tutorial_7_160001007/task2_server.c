#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

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
    listen(socket_desc , 3);
    struct sockaddr_in client;
    for (int i =0; i< 3; i++){
       int new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
       if (new_socket == -1){
          printf("Server: couldn't accept connection\n");
       }
       else{
          printf("Server: Accepted connection\n");
          char message[] = "Hello Client , I have received your connection. But I have to go now, bye\n";
          write(new_socket , message , strlen(message));
        }
    }
   
    close(socket_desc);
  }

}
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>




int main() {
  int socket_desc = socket(AF_INET , SOCK_STREAM , 0);

  struct sockaddr_in server;
  server.sin_addr.s_addr = inet_addr("0.0.0.0");
  server.sin_family = AF_INET;
  server.sin_port = htons( 8080 );
  
  int status = connect(socket_desc , (struct sockaddr *)&server , sizeof(server));
  if (status == -1){
    printf("Client3: Couldn't connect to server\n");
    return 1;
  }
  else{
    printf("Client3: Made Connection\n");
    // char message[] = "Yolo\n";
    // printf("Client3: going to send messege");
    // status = send(socket_desc , message , strlen(message) , 0);
    // if (status == -1){
    //   printf("Client3: Couldn't send message");
    //   return 1;
    // }else{
    //   printf("Client3: Sent messege");
    // }

    char server_reply[2000];
    printf("Client3: Recieving from server\n");
    recv(socket_desc, server_reply , 2000 , 0);
    printf("Client3: Server said %s\n", server_reply);

    close(socket_desc);
  }
  return 0;
}

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
    printf("Client: Couldn't connect to server\n");
    return 1;
  }
  else{
    printf("Client: Made Connection\n");
    int num = 10;
    printf("Client: going to send messege %d \n", num);

    status = send(socket_desc , &num, sizeof(num), 0);
    if (status == -1){
      printf("Client: Couldn't send message");
      close(socket_desc);
      return 1;
    }else{
      printf("Client: Sent messege");
      int ans;
      printf("Client: Recieving from server\n");
      recv(socket_desc, &ans, sizeof(ans), 0);
      printf("Client: Server said %d\n", ans);
    }

  
   

  }
  return 0;
}

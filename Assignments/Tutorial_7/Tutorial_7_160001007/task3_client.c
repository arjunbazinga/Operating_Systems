#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <time.h>


int main() {
  int socket_desc = socket(AF_INET , SOCK_STREAM , 0);

  struct sockaddr_in server;
  server.sin_addr.s_addr = inet_addr("0.0.0.0");
  server.sin_family = AF_INET;
  server.sin_port = htons( 8080 );
  
  clock_t start = clock();
  int timeout = 3;
  int status = -1;
  do {
    printf("Trying to connect to server\n");
    status = connect(socket_desc , (struct sockaddr *)&server , sizeof(server));
    if (status != -1){
      break;
    }
   } while ((clock()-start)/CLOCKS_PER_SEC < 3);
   
   if (status == -1){
    printf("Client: Couldn't connect to server\n");
    }
   else{
    printf("Client: Made Connection\n");
    char server_reply[2000];
    printf("Client: Recieving from server\n");
    recv(socket_desc, server_reply , 2000 , 0);
    printf("Client: Server said %s\n", server_reply);
    close(socket_desc);
  }
  return 0;
}

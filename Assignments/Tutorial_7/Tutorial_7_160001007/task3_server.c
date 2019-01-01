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
    listen(socket_desc , 1);
    struct sockaddr_in client;
   
    int new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (new_socket == -1){
      printf("Server: couldn't accept connection\n");
    }
    else{
      printf("Server: Accepted connection\n");
      int text_s = 100;
      char text[text_s];
      time_t now = time(NULL);
      struct tm *t = localtime(&now);
      strftime(text, sizeof(text)-1, "%d %m %Y %H:%M", t);

      write(new_socket , text, text_s);
    }
  
    close(socket_desc);
  }

}
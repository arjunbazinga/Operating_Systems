#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
  int socket_desc = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server;
  server.sin_addr.s_addr = inet_addr("0.0.0.0");
  server.sin_family = AF_INET;
  server.sin_port = htons(8080);

  int status = connect(socket_desc, (struct sockaddr *)&server, sizeof(server));
  if (status == -1)
  {
    printf("Client: Couldn't connect to server\n");
    return 1;
  }

  printf("Client: Made Connection\n");
  char server_reply[2000];
  printf("Client: Recieving from server\n");
  recv(socket_desc, server_reply, 2000, 0);
  printf("Client: Server said %s\n", server_reply);

  close(socket_desc);

  return 0;
}

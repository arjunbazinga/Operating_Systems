#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main()
{
  char ip_addr[] = "0.0.0.0";

  int socket_desc = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server;
  server.sin_addr.s_addr = inet_addr(ip_addr);
  server.sin_family = AF_INET;
  server.sin_port = htons(8080);

  int status = connect(socket_desc, (struct sockaddr *)&server, sizeof(server));
  if (status == -1)
  {
    printf("Client: Couldn't connect to server\n");
    return 1;
  }
  else
  {
    printf("Client: Made Connection\n");

    int reply_len = 100;
    char reply[reply_len];
    pid_t p = fork();
    if (p == -1)
    {
      printf("Client: Couldn't fork\n");
    }
    else
    {
      if (p == 0)
      {
        while (1)
        {
          recv(socket_desc, reply, reply_len, 0);
          printf("%s", reply);
        }
      }
      else
      {
        while (1)
        {
          scanf("%[^\n]s", reply);
          status = send(socket_desc, reply, reply_len, 0);
          if (status == -1)
          {
            printf("Client: Couldn't send message");
            close(socket_desc);
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

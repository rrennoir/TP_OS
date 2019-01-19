#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>

int main()
{
  int server_sockfd, client_sockfd;
  int server_len, client_len;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  char ch;
  int fd;
  int nread, result; 
  fd_set readfds, testfds;

  /* init */
  FD_ZERO(&readfds);

  /*  Créer un socket */

  server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

  /*  Nommer le socket */
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(9734);
  server_len = sizeof(server_address);
  bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

  /*  Créer une file de connection et attend des clients  */
  listen(server_sockfd, 5);

  /* ajouter socket serveur à la liste de monitorat */
  FD_SET(server_sockfd, &readfds);

  while(1) {
    testfds = readfds;
    printf("server waiting\n");

    result = select(FD_SETSIZE, &testfds, (fd_set*) NULL, (fd_set*) NULL, (struct timeval *) 0);

    if (result == -1) {
      perror("select");
      exit(EXIT_FAILURE);
    }    

    for (fd = 0; fd < FD_SETSIZE; fd++) {
      if (FD_ISSET(fd, &testfds)) {
        if (fd == server_sockfd) {
          client_len = sizeof(client_address);
          client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
          FD_SET(client_sockfd, &readfds);
          printf("adding client on fd %d\n", client_sockfd);
        } else {
          ioctl(fd, FIONREAD, &nread);
          if (nread == 0) {
            close(fd);
            FD_CLR(fd, &readfds);
            printf("removing client on fd %d\n", fd);
          } else {
            read(fd, &ch, 1);
            ch++;
            write(fd, &ch, 1);
          }
        }
      }
    }
  }
}

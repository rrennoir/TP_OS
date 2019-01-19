#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
  int server_sockfd, client_sockfd;
  int server_len, client_len;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  char ch;
  struct sigaction action;

  action.sa_handler = SIG_IGN;
  action.sa_flags = 0;

  sigaction(SIGCHLD, &action, NULL);

  /* Créer un socket pour le serveur */

  server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

  /* Nommer le socket */

  server_address.sin_family = AF_INET;
  /* adresse locale de hôte */
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(9734);;
  server_len = sizeof(server_address);
  bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

  /* Créer une file de connection et attendre des clients */
  listen(server_sockfd, 5);

  while(1) {
    printf("server waiting\n");

    /* Accepter une connection. */

    client_len = sizeof(client_address);
    client_sockfd = accept(server_sockfd, 
        (struct sockaddr *)&client_address, &client_len);

    if (fork() == 0) {
      /* On peut lire/écrire client_sockfd. */
      read(client_sockfd, &ch, 1);
      sleep(5);
      ch++;
      write(client_sockfd, &ch, 1);
      close(client_sockfd);
      exit(0);
    } else {
      close(client_sockfd);
    }
  }
}
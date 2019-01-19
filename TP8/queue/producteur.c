#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "share.h"

char * random_str(int length) {
  int i, rank;
  char alphanum[] = {'a', 'b', 'c', 'd', 'e', \
                     'f', 'g', 'h', 'i', 'j', \
                     'k', 'l', 'm', 'n', 'o', \
                     'p', 'q', 'r', 's', 't', \
                     'u', 'v', 'w', 'x', 'y', \
                     'z', '0', '1', '2', '3', \
                     '4', '5', '6', '7', '8', \
                     '9' };
  int size;
  char * buf;

  size = sizeof(alphanum);

  srand((unsigned int)time(NULL) * length);

  buf = (char *) malloc(length);

  for (i = 0; i < length; i++) {
    rank = rand() % size;
    buf[i] = alphanum[rank];
  }

  buf[i] = '\0';

  return buf;  
}

int main() {
  int i;
  int msg_id;
  struct message * msg;
  char * str;

  msg_id = msgget(MSG_KEY, IPC_CREAT|0666);

  if (msg_id == -1) {
    perror("msgget");
    exit(EXIT_FAILURE);
  }

  msg = (struct message *) malloc(sizeof(struct message));
  /* prepare message */
  msg->type = 1;
 
  for (i = 0; i < 10; i++) {
    str = random_str(i+1);
    printf("I send message %d: %s\n", i, str);
    strcpy(msg->data, str);
    msgsnd(msg_id, msg, MSG_SIZE, 0);
  }
  
  if (msgctl(msg_id, IPC_RMID, NULL) == -1) {
    perror("msgctl");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}

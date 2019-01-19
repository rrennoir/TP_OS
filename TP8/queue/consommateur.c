#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "share.h"

int main() {
  int i;
  int msg_id;
  struct message * msg;

  msg_id = msgget(MSG_KEY, IPC_CREAT|0666);

  if (msg_id == -1) {
    perror("msgget");
    exit(EXIT_FAILURE);
  }
 
  while (msgrcv(msg_id, msg, MSG_SIZE, 0, 0) > 0) {
    printf("message received: %s\n", msg->data);
  } 

  exit(EXIT_SUCCESS);
}

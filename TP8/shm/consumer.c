#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "share.h"

int main() {
  int shm_id;
  void *shared_memory = (void *)0;
  struct command * cmd;
  int running = 1;

  shm_id = shmget((key_t) KEY_ID, sizeof(struct command), IPC_CREAT|0666);

  if (shm_id == -1) {
    perror("shmget");
    exit(EXIT_FAILURE);
  }

  shared_memory = shmat(shm_id, NULL, 0);

  cmd = (struct command*) shared_memory;
  
  (*cmd).start = 0;

  while (running) {
    if ((*cmd).start == 1) {
      printf("Input value is: %s\n", cmd->value);
      fflush(stdout);
      sleep(1); 
      
      cmd->start = 0;

      if (strcmp((*cmd).value, "end") == 0) {
        running = 0;
      }
    }
  }

  if (shared_memory == (void *) -1) {
    perror("shmat");
    exit(EXIT_FAILURE);
  }

  /* after usage */
  shmdt(shared_memory);

  return 0;
}

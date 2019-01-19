#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    for (int i = 0; i < 4; i++){
        
        int pid;
        pid = fork();
        int randomNb = rand();

        switch (pid)
        {
            case -1:
                printf("Cannot create a process.\n");
                break;
        
            case 0:
                printf("I'm the son pid: %d and my random number is: %d.\n\n", getpid(), randomNb);
                exit(0);
                break;

            default:
                printf("I'm the father(pid: %d) of the process son pid: %d and is random number is: %d.\n", getpid(), pid, randomNb);
                break;
        }
        wait(NULL);
    }
    return 0;
}
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void)
{
    int pid;
    pid = fork();
    
    switch (pid)
    {
        case -1:
            printf("Cannot create a process.\n");
            break;
    
        case 0:
            printf("je suis le fils et mon pid: %d, ppid: %d.\n", getpid(), getppid());
            exit(0);
            break;

        default:
            printf("Je suis le père du processus fils pid: %d\n.", getpid());
            break;
    }
    wait(NULL);
    return 0;
}

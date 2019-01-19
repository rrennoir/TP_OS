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
    for (int i = 0; i < 2; i++){
        
        int pid;
        int maxRand;
        pid = fork();

        if (i == 0){
            maxRand = 25;
        }
        else{
            maxRand = 50;
        }

        int randomNb = rand() % maxRand;

        switch (pid)
        {
            case -1:
                printf("Cannot create a process.\n");
                break;
        
            case 0:
                printf("I'm the son my random number is: %d.\n", randomNb);
                exit(0);
                break;

            default:
                break;
        }
        wait(NULL);
    }
    return 0;
}
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(void)
{
    printf("Parent PID: %d\n", getpid());

    for (int i = 0; i < 3; i++){
        
        int pid;
        pid = fork();

        switch (pid)
        {
            case -1:
                printf("Cannot create a process.\n");
                break;
        
            case 0:
                printf("level 1, pid: %d, parent: %d\n", getpid(), getppid());
                for (int j = 0; j < 2 && i != 2; j++){
                    
                    pid = fork();

                    switch (pid)
                    {
                        case -1:
                            printf("Cannot create a process.\n");
                            break;

                        case 0:
                            if (!(j == 1 && i == 1)){
                            printf("level 2, pid: %d, parent: %d\n", getpid(), getppid());}

                            if (i == 0 && j == 0){
                                pid = fork();
                                
                                switch (pid)
                                {
                                    case 0:
                                        printf("level 3, pid: %d, parent: %d\n\n", getpid(), getppid());
                                        exit(0);
                                        break;
                                
                                    default:
                                        break;
                                }
                                wait(NULL);
                            }

                            exit(0);
                            break;

                        default:
                            break;
                    }
                    wait(NULL);
                }

                exit(0);
                break;

            default:
                break;
        }
        wait(NULL);
    }
    return 0;
}

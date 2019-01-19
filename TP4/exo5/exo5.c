#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(int argc, char *argv[])
{
    int fd, oldOut, pid;
    char** new_argv;

    new_argv = malloc((argc) * sizeof *new_argv);
    for(int i = 0; i < argc - 2; ++i)
    {
        size_t length = strlen(argv[i])+1;
        new_argv[i] = malloc(length);
        memcpy(new_argv[i], argv[i + 1], length);
    }

    if (fork() == 0)
    {
        if ((fd = open(argv[argc - 1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
        {
            printf("File not given in the last parameter.\n");
            return;
        }
        oldOut = dup(1);
        dup2(fd, 1);
        close(fd);

        if (execvp(argv[1], new_argv) == -1){
            dup2(oldOut, 1);
            printf("Exec failed.\n");
            return;
        }
    }
    wait(NULL);
}
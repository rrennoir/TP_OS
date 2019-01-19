#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/wait.h>

char* readFile(char const *argv[])
{
    int c;
    int n = 0;
    char *text;
    FILE *file;

    file = fopen(argv[1], "r");

    if(file == NULL)
    {
        printf("Failed to open the file.\n");
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    text = malloc(f_size);

    while((c = fgetc(file)) != EOF)
    {
        text[n++] = (char)c;
    }
    text[n] = '\0';
    fclose(file);  
    return text;
}

void printMaxCharacter(char *text, int max)
{
    int n = 0;
    while((text[n] != '\0') && (n < max))
    {
        printf("%c", text[n]);
        n++;
    }
    printf("\n");
}

void main(int argc, char const *argv[])
{
    int maxFather = 10;
    int maxSon = 5;
    int pid;
    char *text;

    if(argc < 2)
    {
        printf("Not enought arguments, 1 needed: FileOrigine");
    }
    text = readFile(argv);
    pid = fork();

    switch (pid)
    {
        case -1:
            printf("Cannot create a process.\n");
            break;
    
        case 0:
            printMaxCharacter(text, maxSon);
            exit(0);
            break;

        default:
            printMaxCharacter(text, maxFather);
            break;
    }
    wait(NULL);

    free(text);
}
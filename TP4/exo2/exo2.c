#include <stdio.h>
#include <stdlib.h> 

void main(int argc, char const *argv[])
{
    int c;
    FILE *file;
    FILE *fileCopy;

    fileCopy = fopen(argv[2], "w");
    file = fopen(argv[1], "r");

    if(file)
    {
        while((c = fgetc(file)) != EOF)
        {
            fprintf(fileCopy, "%c", c);
        }
        fclose(file);
        fclose(fileCopy);
    }
    else
    {
        printf("File do not exist.\n");
    }
}
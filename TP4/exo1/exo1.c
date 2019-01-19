#include <stdio.h>
#include <stdlib.h> 

void main(int argc, char const *argv[])
{
    int c;
    FILE *file;

    file = fopen(argv[1], "r");

    if (file)
    {
        while((c = fgetc(file)) != EOF)
        {
            putchar(c);
        }     
        fclose(file);
    }
}

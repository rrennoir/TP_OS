#include <stdio.h>

void main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        printf("%s\n", argv[1]);
    }
    else
    {
        printf("One arguments should be given.\n");
    } 
}

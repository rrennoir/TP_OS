#include <stdio.h>

void main(int argc, char *argv[]){

    int i = 0, j, length = 0;
    
    while (argv[1][i] != '\0'){
        length ++;
        i ++;
    }

    for(i = length - 1, j = 0; i >= 0, j <= length - 1; i--, j++)
    {
        if (argv[1][i] != argv[1][j]){
            printf("The string isn't a palindrome.\n");
            return;
        }
    }
    printf("The string is a palidrome.\n");
}
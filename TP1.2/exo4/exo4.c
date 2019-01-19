#include <stdio.h>

void main(void){
    int i = 0, length = 0;
    char string[50];

    printf("Enter a string.\n");
    scanf("%49s", string);

    while (string[i] != '\0'){
        length ++;
        i ++;
    }
    printf("String length is %d.\n", length);
}
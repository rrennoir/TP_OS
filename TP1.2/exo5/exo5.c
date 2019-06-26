#include <stdio.h>

void palidrome(char string[4096], int length)
{
    int i, j;

    for(i = length - 1, j = 0; i >= 0, j <= length - 1; i--, j++)
        {
            if (string[i] != string[j])
            {
                printf("The string isn't a palindrome.\n");
                return;
            }
        }
        printf("The string is a palidrome.\n");
}

void main(void)
{
    int i = 0, length = 0;
    char string[4096];

    printf("Enter a string.\n");
    scanf("%4095s", string);

    while (string[i] != '\0')
    {
        length ++;
        i ++;
    }
    palidrome(string, length);
}
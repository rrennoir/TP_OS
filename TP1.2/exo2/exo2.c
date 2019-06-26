#include <stdio.h>

void main(void)
{
    int nb, somme = 0;

    printf("Give a integer\n");
    scanf("%d", &nb);
    printf("-----\n");

    if ((nb % 2) != 1)
    {
        nb --;
    }
    while(nb > 0)
    {
        printf("%d\n", nb);

        somme += nb;
        nb -= 2;
    }
    printf("-----\nResult is: %d\n", somme);
}

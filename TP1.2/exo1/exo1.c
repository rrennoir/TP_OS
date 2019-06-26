#include <stdio.h>

int PGCD (int a, int b)
{
    int diff, tmp;

    while (a != b)
    {
        tmp = a;
        a = b;
        b = tmp;

        if (a < b)
        {
            tmp = b;
            b = a;
            a = tmp;
        }
        diff = a - b;

        a = b;
        b = diff;
    }
    return a;
}

void main(void)
{
    int nb1 = 0, nb2 = 0, result;

    printf("Give 2 integer.\n");
    scanf("%d %d", &nb1, &nb2);
    printf("-------\n");

    result = PGCD(nb1, nb2);
    printf("\nThe PGCD of %d and %d is: %d\n", nb1, nb2 ,result);
}

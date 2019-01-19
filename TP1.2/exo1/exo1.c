#include <stdio.h>

int PGCD (int a, int b){
    int difference;
    int temp;

    while (a != b){
        temp = a;
        a = b;
        b = temp;
        if (a < b){
            temp = b;
            b = a;
            a = temp;
        }

        difference = a - b;

        a = b;
        b = difference;
    }
    return a;
}

void main(void)
{
    int nb1 = 0;
    int nb2 = 0;
    int result;

    printf("Give 2 integer.\n");
    scanf("%d %d", &nb1, &nb2);
    printf("-------\n");

    result = PGCD(nb1, nb2);
    printf("\nThe PGCD of %d and %d is: %d\n", nb1, nb2 ,result);
}

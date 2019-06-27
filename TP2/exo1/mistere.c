#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int getch(void);
void ungetch(int);

#define SIZE 5

int main()
{
    int n, array[SIZE], getint(int *);
  
    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
    {
        // To better understand what happend.
        for (int i = 0; i < SIZE; i++)
        {
            if (i <= n)
            {
                printf("array[%d] = %d\n", i, array[i]);
            }
            else
            {
                printf("array[%d] = not initialized\n", i);
            }
        }
    }
    return 0;
}

int getint(int *pn)
{    
    int c, sign;
    
    while (isspace(c = getchar()));
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') 
    {
        ungetc(c, stdin);
        return 0;
    }
  
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getchar();
  
    for (*pn = 0; isdigit(c); c = getchar())
        *pn = 10 * *pn + (c - '0');
        *pn *= sign;
  
    if (c != EOF)
        ungetc(c, stdin);

    return c; 
}

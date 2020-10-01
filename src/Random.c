#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int random, flag;
    int i, j, n, m;

    srand((unsigned) time(NULL));
    scanf("%d%d", &n, &m);
    int num[n];

    while (i < n)
    {
        flag = 0, i = 0;

        random = rand() % m + 1;
        for (j = 0; j < i; j++)
            if (num[j] == random)
                flag = 1;
        if (flag)
            continue;
        num[i++] = random;
    }
    for (i = 0; i < n; i++)
        printf("%d ", num[i]);
    printf("\n");

    return 0;
}
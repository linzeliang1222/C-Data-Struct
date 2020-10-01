#include <stdio.h>

int main(void)
{
    int n, m;
    int i, j, min;
    int t = 0, count = 1;

    scanf("%d%d", &n, &m);
    int rectangle[n][m];

    min = n < m ? n : m;
    while (t < min / 2 + 2)
    {
        for (i = t; i < m - t; i++)
            rectangle[t][i] = count++;

        for (i = t + 1; i < n - t; i++)
            rectangle[i][m-t-1] = count++;

        for (i = m - t - 2; i >= t; i--)
        {
            if (n != m && t >= min/2)
                break;
            rectangle[n-t-1][i] = count++;
        }

        for (i = n - t - 2; i > t; i--)
        {
            if (n != m && t >= min/2)
                break;
            rectangle[i][t] = count++;
        }
        t++;
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d\t", rectangle[i][j]);
        }
        printf("\n");
    }

    return 0;
}
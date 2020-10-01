#include <stdio.h>

int main(void)
{
    int n, m;
    int i, j;
    int t = 0, count = 1;

    scanf("%d%d", &n, &m);
    int rectangle[n][m];

    while (t < m / 2 + 1)
    {
        /* ��ӡ����һ�� */
        for (i = t; i < m - t; i++)
            rectangle[t][i] = count++;
        /* ��ӡ�ұ�һ�� */ 
        for (i = t + 1; i < n - t; i++)
            rectangle[i][m-t-1] = count++;
        /* ��ӡ����һ�� */
        for (i = m - t - 2; i >= t; i--)
            rectangle[n-t-1][i] = count++;
        /* ��ӡ���һ�� */
        for (i = m - t - 2; i > t; i--)
            rectangle[i][t] = count++;
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
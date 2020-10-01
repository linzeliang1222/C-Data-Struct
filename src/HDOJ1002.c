/* HDOJ 1002 */
/* http://acm.hdu.edu.cn/showproblem.php?pid=1002 */
#include <stdio.h>
#include <string.h>

/* �������֮�� */
void sum(char *lst1, char *lst2);

int main(void)
{
    char x[100][1000], y[100][1000]; // ����������ά������������Ƶ�����
    int n;                           // ���Ҫ����Ĵ���
    int h = 0, i = 0, j = 0, k = 1;  // i,j�ֱ����x��y�������飬ͬ����Ŵ����������k��ӡCase������h��ȡ��ά����ֵ����sum����

    scanf("%d", &n);

    while (n--)
    {
        scanf("%s", x[i++]);
        scanf("%s", y[j++]);
    }
    while (i--)
    {
        /* �׺�β�����п��� */
        if (k == 1)
            printf("Case %d:\n%s + %s = ", k++, x[h], y[h]);
        else
            printf("\nCase %d:\n%s + %s = ", k++, x[h], y[h]);
        sum(x[h], y[h]); // ����sum��������
        h++;
    }

    return 0;
}

void sum(char x[], char y[])
{
    int lst1[1000] = {0}, lst2[1000] = {0}, total[1000] = {0}; // ����������������ֱ��������x��y��ÿһλ���ֺ���Ӻ�Ľ��ÿһλ���ӣ�����Ϊ1000
    int i, n;
    int count = 0, t = 0; // count������Ӻ����м�λ
    int extend = 0; // ����Ƿ�������չλ���磺���ǰ���λΪ3λ����Ӻ����λΪ4λ

    /* ���ַ�����ÿһλ���뵽���������� */
    for (i = 0; i < strlen(x); i++)
        lst1[i] = (int)x[strlen(x) - 1 - i] - 48;
    for (i = 0; i < strlen(y); i++)
        lst2[i] = (int)y[strlen(y) - 1 - i] - 48;

    for (i = 0; i < (strlen(x) > strlen(y) ? strlen(x) : strlen(y)); i++, count++)
    {
        n = lst1[i] + lst2[i] + t; // ������ÿλ����ټ����Ƿ��λ�Ľ��
        /* ����10����1 */
        if (n >= 10)
        {
            total[i] = n % 10;
            t = 1;
            /* ��չ1λ */
            if (i == (strlen(x) > strlen(y) ? strlen(x) : strlen(y)) - 1)
            {
                total[i+1] = 1;
                extend = 1;
            }
        }
        /* С��10������1 */
        else
        {
            total[i] = n;
            t = 0;
        }
    }
    /* ���ڸ�λ�������һλ�����ԴӺ���ǰ���δ�ӡ��ÿһλ */
    for (i = count + extend - 1; i >= 0; i--)
    {
        printf("%d", total[i]);
    }
    printf("\n");
}
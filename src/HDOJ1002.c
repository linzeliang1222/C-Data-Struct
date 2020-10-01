/* HDOJ 1002 */
/* http://acm.hdu.edu.cn/showproblem.php?pid=1002 */
#include <stdio.h>
#include <string.h>

/* 计算大数之和 */
void sum(char *lst1, char *lst2);

int main(void)
{
    char x[100][1000], y[100][1000]; // 定义两个二维数组存放输入待计的算数
    int n;                           // 存放要计算的次数
    int h = 0, i = 0, j = 0, k = 1;  // i,j分别控制x与y两个数组，同步存放待计算的数，k打印Case次数，h读取二维数组值传给sum函数

    scanf("%d", &n);

    while (n--)
    {
        scanf("%s", x[i++]);
        scanf("%s", y[j++]);
    }
    while (i--)
    {
        /* 首和尾不能有空行 */
        if (k == 1)
            printf("Case %d:\n%s + %s = ", k++, x[h], y[h]);
        else
            printf("\nCase %d:\n%s + %s = ", k++, x[h], y[h]);
        sum(x[h], y[h]); // 调用sum函数计算
        h++;
    }

    return 0;
}

void sum(char x[], char y[])
{
    int lst1[1000] = {0}, lst2[1000] = {0}, total[1000] = {0}; // 定义三个整形数组分别用来存放x、y中每一位数字和相加后的结果每一位数子，上限为1000
    int i, n;
    int count = 0, t = 0; // count计数相加后结果有几位
    int extend = 0; // 检查是否结果有扩展位，如：相加前最大位为3位，相加后最大位为4位

    /* 将字符串的每一位输入到整形数组中 */
    for (i = 0; i < strlen(x); i++)
        lst1[i] = (int)x[strlen(x) - 1 - i] - 48;
    for (i = 0; i < strlen(y); i++)
        lst2[i] = (int)y[strlen(y) - 1 - i] - 48;

    for (i = 0; i < (strlen(x) > strlen(y) ? strlen(x) : strlen(y)); i++, count++)
    {
        n = lst1[i] + lst2[i] + t; // 两个数每位相加再加上是否进位的结果
        /* 超过10，进1 */
        if (n >= 10)
        {
            total[i] = n % 10;
            t = 1;
            /* 扩展1位 */
            if (i == (strlen(x) > strlen(y) ? strlen(x) : strlen(y)) - 1)
            {
                total[i+1] = 1;
                extend = 1;
            }
        }
        /* 小于10，不进1 */
        else
        {
            total[i] = n;
            t = 0;
        }
    }
    /* 由于各位在数组第一位，所以从后往前依次打印出每一位 */
    for (i = count + extend - 1; i >= 0; i--)
    {
        printf("%d", total[i]);
    }
    printf("\n");
}
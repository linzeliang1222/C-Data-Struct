/* HDOJ 1004 */
/* http://acm.hdu.edu.cn/showproblem.php?pid=1004 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(void)
{
    int i, j, n;
    
    scanf("%d", &n);
    while (n > 0)
    {
        char colors[1000][16];   // 储存用户的颜色的数组，且查看是否重复
        char temp[16];           // 用户将要存入的颜色字符串
        int count[1000] = {0};   // 计数各个颜色出现的次数
        int max = 0, current = 0;;

        for (i = 0; i < n; i++)
        {
            scanf("%s", temp);

            /* 检测用户输入的颜色是否存在 */
            bool flag = true;
            for (j = 0; j < current; j++)
            {
                if (!strcmp(temp, colors[j])) // 表示当前颜色已存在
                {
                    count[current]++;
                    flag = false; // 表示找到该颜色
                    strcpy(colors[current], temp); // 将新的颜色存入二维数组中
                }
            }
            /* 用户颜色不存在 */
            if (flag)
            {
                strcpy(colors[current], temp);
                count[current]++;
            }
            current++;
        }

        for (i = 0; i < current; i++)
        {
            if (max < count[i])
            {
                max = count[i];
                strcpy(temp, colors[i]);
            }
        }
        printf("%s\n", temp);

        scanf("%d", &n);
    }

    return 0;
}
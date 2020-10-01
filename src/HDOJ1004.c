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
        char colors[1000][16];   // �����û�����ɫ�����飬�Ҳ鿴�Ƿ��ظ�
        char temp[16];           // �û���Ҫ�������ɫ�ַ���
        int count[1000] = {0};   // ����������ɫ���ֵĴ���
        int max = 0, current = 0;;

        for (i = 0; i < n; i++)
        {
            scanf("%s", temp);

            /* ����û��������ɫ�Ƿ���� */
            bool flag = true;
            for (j = 0; j < current; j++)
            {
                if (!strcmp(temp, colors[j])) // ��ʾ��ǰ��ɫ�Ѵ���
                {
                    count[current]++;
                    flag = false; // ��ʾ�ҵ�����ɫ
                    strcpy(colors[current], temp); // ���µ���ɫ�����ά������
                }
            }
            /* �û���ɫ������ */
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
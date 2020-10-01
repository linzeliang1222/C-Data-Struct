#include <stdio.h>
#include <string.h>

typedef char * String;

void Get_next(String P, int next[]);
int Index_KMP(String S, String P);

int main(void)
{
    String S = "aaaabcde";
    String P = "abc";

    printf("%d\n", Index_KMP(S, P));

    return 0;
}

/* 得到next数组 */
void Get_next(String P, int next[])
{
    int pLen = strlen(P);
    int i = -1;
    int j = 0;
    next[0] = -1;

    while (j < pLen)
    {
        if (i == -1 || P[i] == P[j])
        {
            j++;
            i++;
            if (P[i] != P[j])      // 若当前字符与前缀字符不同，则当前i值为next在j中的位置
                next[j] = i;
            else                   // 如果与前缀字符相同，则将前缀字符的next值赋值给next在j位置的值
                next[j] = next[i];
        }
        else
        {
            i = next[i];          // 若字符不相同，则i回溯
        }
    }
}

/* KMP模式匹配算法 */
int Index_KMP(String S, String P)
{
    int i = 0;            // 用于主串当前位置的下标
    int j = 0;            // 用于子串P中当前位置的下标
    int sLen = strlen(S); // 主串S的长度
    int pLen = strlen(P); // 字串P的长度
    int next[255];        // 定义next数组

    Get_next(P, next);    // 对字串进行分析，得到next数组
    while (i < sLen && j < pLen)
    {
        if (j == -1 || S[i] == P[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];   // j退回合适的位置，i的位置不变
        }
    }
    if (j == pLen)
        return i - j;
    else
        return -1;
}
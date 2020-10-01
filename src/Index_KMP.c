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

/* �õ�next���� */
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
            if (P[i] != P[j])      // ����ǰ�ַ���ǰ׺�ַ���ͬ����ǰiֵΪnext��j�е�λ��
                next[j] = i;
            else                   // �����ǰ׺�ַ���ͬ����ǰ׺�ַ���nextֵ��ֵ��next��jλ�õ�ֵ
                next[j] = next[i];
        }
        else
        {
            i = next[i];          // ���ַ�����ͬ����i����
        }
    }
}

/* KMPģʽƥ���㷨 */
int Index_KMP(String S, String P)
{
    int i = 0;            // ����������ǰλ�õ��±�
    int j = 0;            // �����Ӵ�P�е�ǰλ�õ��±�
    int sLen = strlen(S); // ����S�ĳ���
    int pLen = strlen(P); // �ִ�P�ĳ���
    int next[255];        // ����next����

    Get_next(P, next);    // ���ִ����з������õ�next����
    while (i < sLen && j < pLen)
    {
        if (j == -1 || S[i] == P[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];   // j�˻غ��ʵ�λ�ã�i��λ�ò���
        }
    }
    if (j == pLen)
        return i - j;
    else
        return -1;
}
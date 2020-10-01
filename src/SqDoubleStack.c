#include <stdio.h>

#define MAXSIZE 20
#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0

typedef int SElemType;
typedef int Status;

/* ��ջ����ռ�ṹ */
typedef struct
{
    SElemType data[MAXSIZE];
    int top1;
    int top2;
} SqDoubleStack;

Status Push(SqDoubleStack * S, SElemType e, int stackNumber);
Status Pop(SqDoubleStack * S, SElemType * e, int stackNumber);

int main(void)
{
    return 0;
}

/* ����Ԫ��eΪ�µ�ջ��Ԫ�� */
Status Push(SqDoubleStack * S, SElemType e, int stackNumber)
{
    if (S->top1 + 1 == S->top2) // ջ������������push��Ԫ����
        return ERROR;
    if (stackNumber == 1)       // ջ1����Ԫ�ؽ�ջ
        S->data[++S->top1] = e; // ��ջ1����top1+1�������Ԫ�ظ�ֵ
    else if (stackNumber == 2)  // ջ2����Ԫ�ؽ�ջ
        S->data[--S->top2] = e; // ��ջ2����top2-1�������Ԫ�ظ�ֵ
    return OK;
}

/* ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR */
Status Pop(SqDoubleStack * S, SElemType * e, int stackNumber)
{
    if (stackNumber == 1)
    {
        if (S->top1 == -1)
            return ERROR;       // ˵��ջ1�Ѿ��ǿ�ջ�����
        *e = S->data[S->top1--]; // ��ջ1��ջ��Ԫ�س�ջ
    }
    else if (stackNumber == 2)
    {
        if (S->top2 == MAXSIZE)
            return ERROR;       // ˵��ջ2�Ѿ��ǿ�ջ�����
        *e = S->data[S->top2++];// ��ջ2��ջ��Ԫ�س�ջ
    }
    return OK;
}

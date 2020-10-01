#include <stdio.h>

#define MAXSIZE 20
#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0

typedef int SElemType;
typedef int Status;

/* 两栈共享空间结构 */
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

/* 插入元素e为新的栈顶元素 */
Status Push(SqDoubleStack * S, SElemType e, int stackNumber)
{
    if (S->top1 + 1 == S->top2) // 栈已满，不能再push新元素了
        return ERROR;
    if (stackNumber == 1)       // 栈1有新元素进栈
        S->data[++S->top1] = e; // 若栈1则先top1+1后给数组元素赋值
    else if (stackNumber == 2)  // 栈2有新元素进栈
        S->data[--S->top2] = e; // 若栈2则先top2-1后给数组元素赋值
    return OK;
}

/* 若栈不空，则删除S的栈项元素，用e返回其值，并返回OK；否则返回ERROR */
Status Pop(SqDoubleStack * S, SElemType * e, int stackNumber)
{
    if (stackNumber == 1)
    {
        if (S->top1 == -1)
            return ERROR;       // 说明栈1已经是空栈，溢出
        *e = S->data[S->top1--]; // 将栈1的栈顶元素出栈
    }
    else if (stackNumber == 2)
    {
        if (S->top2 == MAXSIZE)
            return ERROR;       // 说明栈2已经是空栈，溢出
        *e = S->data[S->top2++];// 将栈2的栈顶元素出栈
    }
    return OK;
}

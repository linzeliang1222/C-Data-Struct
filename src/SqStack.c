#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20
#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0

typedef int Status;
typedef int ElemType; // ElemType类型根据实际情况而定，这里假设为int

typedef struct
{
    ElemType data[MAXSIZE];
    int top; // 栈顶指针
} SqStack;


Status InitStack(SqStack ** S);
Status Push(SqStack * S, ElemType e);
Status Pop(SqStack * S, ElemType * e);
Status StackTraverse(SqStack * S);
Status StackClear(SqStack * S);
Status StackEmpty(SqStack * S);
Status GetTop(SqStack * S, ElemType * e);
Status StackDestory(SqStack * S);
int StackLength(SqStack * S);
void visit(ElemType e);

int main(void)
{
    SqStack * S;
    ElemType e;

    if (InitStack(&S))
        printf("初始化顺序栈成功！\n");
    printf("\n");

    for (int i = 0; i < 10; i++)
        Push(S, i);
    printf("入栈后栈内元素为: ");
    StackTraverse(S);
    GetTop(S, &e);
    printf("此时栈顶元素为: %d\n", e);
    printf("此时栈的长度为: %d\n", StackLength(S));
    printf("\n");

    printf("开始弹出栈顶元素...\n");
    Pop(S, &e);
    printf("弹出的栈顶元素为: %d\n", e);
    printf("此时的栈内元素为: ");
    StackTraverse(S);
    GetTop(S, &e);
    printf("此时栈顶元素为: %d\n", e);
    printf("此时栈的长度为: %d\n", StackLength(S));
    printf("\n");

    printf("该栈是否为空(1:是 0:否): %d\n", StackEmpty(S));
    printf("开始清空栈...\n");
    if (StackClear(S))
        printf("清空栈成功！\n");
    else
        printf("清空栈失败！\n");
    printf("此时该栈是否为空(1:是 0:否): %d\n", StackEmpty(S));
    printf("\n");

    printf("开始销毁栈...\n");
    if (StackDestory(S))
        printf("销毁栈成功！\n");

    return 0;
}

/* 初始化顺序栈 */
Status InitStack(SqStack ** S)
{
    *S = (SqStack *) malloc(sizeof(SqStack)); // 申请一个栈内存空间
    if ((*S) == NULL)
        return ERROR;
    (*S)->top = -1;
    return OK;
}

/* 插入元素e为新的栈顶元素 */
Status Push(SqStack * S, ElemType e)
{
    if (S->top == MAXSIZE-1) // 栈满
        return ERROR;
    S->top++;                // 栈顶指针加一
    S->data[S->top] = e;     // 将新插入元素夫赋值给栈顶空间
    return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回EORROR */
Status Pop(SqStack * S, ElemType * e)
{
    if (S->top == -1)     // 栈满
        return ERROR;
    *e = S->data[S->top]; // 将要删除的栈顶元素赋值给e
    S->top--;             // 栈顶指针减一
    return OK;
}

/* 遍历栈 */
Status StackTraverse(SqStack * S)
{
    if (S->top == -1) // 栈空
        return ERROR;
    for (int i = 0; i <= S->top; i++)
        visit(S->data[i]);
    printf("\n");
    return OK;
}

/* 清空栈 */
Status StackClear(SqStack * S)
{
    S->top = -1; // 栈顶指针变为-1
    return OK;
}

/* 判断栈是否为空，若为空返回TRUE，否则返回FALSE */
Status StackEmpty(SqStack * S)
{
    if (S->top == -1)
        return TRUE;
    else
        return FALSE;
}

/* 获取栈顶元素赋值给e */
Status GetTop(SqStack * S, ElemType * e)
{
    *e = S->data[S->top];
    return OK;
}

/* 销毁栈，释放内存空间 */
Status StackDestory(SqStack * S)
{
    if (S->top != -1)
    {
        printf("该栈不为空，请清空栈后再进行销毁操作！\n");
        return ERROR;
    }
    else
        free(S);
    return OK;
}

/* 获取栈的长度 */
int StackLength(SqStack * S)
{
    return S->top + 1;
}

/* 打印栈元素 */
void visit(ElemType e)
{
    printf("%d ", e);
}

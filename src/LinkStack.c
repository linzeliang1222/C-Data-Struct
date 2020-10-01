#include <stdio.h>
#include <stdlib.h>

#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0

typedef int Status;
typedef int ElemType;

typedef struct StackNode
{
    ElemType data;           // 数据域
    struct StackNode * next; // 指针域
} StackNode, * LinkStackPtr;
typedef struct
{
    LinkStackPtr top; // 栈顶指针
    int count;        // 统计栈的元素个数
} LinkStack, * LinkStackTop;

Status InitStack(LinkStackTop * S);
Status Push(LinkStackTop * S, ElemType e);
Status Pop(LinkStackTop * S, ElemType * e);
Status StackTraverse(LinkStackTop S);
Status ClearStack(LinkStackTop * S);
Status StackEmpty(LinkStackTop S);
Status GetTop(LinkStackTop S, ElemType * e);
Status StackDestory(LinkStackTop * S);
int StackLength(LinkStackTop S);
void visit(ElemType e);

int main(void)
{
    LinkStackTop S;
    ElemType e;

    if (InitStack(&S))
        printf("初始化链栈成功！");
    printf("\n");

    for (int i = 0; i < 10; i++)
        Push(&S, i);
    printf("入栈后栈内的元素为: ");
    StackTraverse(S);
    GetTop(S, &e);
    printf("此时栈顶的元素为: %d\n", e);
    printf("此时栈的长度为: %d\n", StackLength(S));
    printf("\n");

    printf("开始弹出栈顶元素...\n");
    Pop(&S, &e);
    printf("弹出的栈顶元素为: %d\n", e);
    printf("此时栈内的元素为: ");
    StackTraverse(S);
    GetTop(S, &e);
    printf("此时栈顶的元素为: %d\n", e);
    printf("此时栈的长度为: %d\n", StackLength(S));
    printf("\n");

    printf("该栈是否为空(1:是 0:否): %d\n", StackEmpty(S));
    printf("开始清空栈...\n");
    if (ClearStack(&S))
        printf("清空栈成功！\n");
    else
        printf("清空栈失败！\n");
    printf("此时该栈是否为空(1:是 0:否): %d\n", StackEmpty(S));
    printf("\n");

    printf("开始销毁栈...\n");
    if (StackDestory(&S))
        printf("销毁栈成功!\n");

    return 0;
}

/* 初始化链栈 */
Status InitStack(LinkStackTop * S)
{
    *S = (LinkStackTop) malloc(sizeof(LinkStack));
    (*S)->top = NULL;
    (*S)->count = 0;
    return OK;
}

/* 插入元素e为新的栈顶元素 */
Status Push(LinkStackTop * S, ElemType e)
{
    LinkStackTop p;
    LinkStackPtr q;
    p = *S;
    q = (LinkStackPtr) malloc(sizeof(StackNode));
    if (!q)
        return ERROR;
    q->next = p->top;
    p->top = q;
    q->data = e;
    p->count++;
    return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回EORROR */
Status Pop(LinkStackTop * S, ElemType * e)
{
    LinkStackTop p;
    LinkStackPtr q;
    p = *S;
    q = p->top;
    if (!q)
        return ERROR;
    p->top = q->next;
    *e = q->data;
    free(q);
    p->count--;
    return OK;
}

/* 遍历栈 */
Status StackTraverse(LinkStackTop S)
{
    LinkStackPtr p;
    p = S->top;
    if (!p)
        return ERROR;
    while (p)
    {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

/* 清空栈 */
Status ClearStack(LinkStackTop * S)
{
    LinkStackTop p;
    LinkStackPtr q, r;
    p = *S;
    if (!(p->top))
        return ERROR;
    q = p->top;
    while (q)
    {
        r = q->next;
        free(q);
        q = r;
    }
    p->top = NULL;
    p->count = 0;
    return OK;
}

/* 判断栈是否为空，若为空返回TRUE，否则返回FALSE */
Status StackEmpty(LinkStackTop S)
{
    if (S->count == 0)
        return TRUE;
    else
        return FALSE;
}

/* 获取栈顶元素，赋值给e */
Status GetTop(LinkStackTop S, ElemType * e)
{
    if (!(S->top))
        return ERROR;
    *e = S->top->data;
    return OK;
}

/* 清空并销毁栈*/
Status StackDestory(LinkStackTop * S)
{
    LinkStackTop p;
    LinkStackPtr q, r;
    p = *S;
    q = p->top;
    while (q)
    {
        r = q->next;
        free(q);
        q = r;
    }
    free(p);
    return OK;
}

/* 获取栈的长度 */
int StackLength(LinkStackTop S)
{
    return S->count;
}

void visit(ElemType e)
{
    printf("%d ", e);
}

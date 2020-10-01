#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20 
#define TRUE    1
#define FALSE   0
#define OK      1
#define ERROR   0

typedef int Status;
typedef int ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int length;
} SqList;

Status InitList(SqList * L);
Status ListEmpty(SqList L);
Status ClearList(SqList * L);
Status GetElem(SqList L, int i, ElemType * e);
Status ListInsert(SqList * L, int i, ElemType e);
Status ListDelete(SqList * L, int i, ElemType * e);
Status ListTraverse(SqList L);
void visit(ElemType c);
void unionL(SqList * La, SqList Lb);
int LocateElem(SqList L, ElemType e);
int ListLength(SqList L);

int main(void)
{
    SqList L;
    ElemType e;
    Status i;
    int j, k;

    i = InitList(&L);
    printf("初始化L�?: L.length = %d\n", L.length);
    for (j = 1; j <= 5; j++)
        i = ListInsert(&L, 1, j);
    printf("在L的表头插�?1-5次后: L.data = ");
    ListTraverse(L);

    printf("L.length = %d\n", L.length);
    i = ListEmpty(L);
    printf("L是否�?: %d(1:�? 0:�?)\n", i);

    i = ClearList(&L);
    printf("清空L�?: L.length = %d\n", L.length);
    i = ListEmpty(L);
    printf("L是否�?: %d(1:�? 0:�?)\n", i);

    for (j = 1; j <= 10; j++)
        ListInsert(&L, j, j);
    printf("在L的表尾依次插�?1�?10后：L.data = ");
    ListTraverse(L);

    printf("L.length = %d\n", L.length);

    ListInsert(&L, 1, 0);
    printf("在L的表头插�?0�?: L.data = ");
    ListTraverse(L);
    printf("L.length = %d\n", L.length);

    GetElem(L, 5, &e);
    printf("�?5个元素的值为: %d\n", e);
    for (j = 3; j <= 4; j++)
    {
        k = LocateElem(L, j);
        if (k)
            printf("�?%d个元素的值为%d\n", k, j);
        else
            printf("没有�?%d的元素\n", j);
    }

    k = ListLength(L);
    for (j = k + 1; j >= k; j--)
    {
        i = ListDelete(&L, j, &e);
        if (i == ERROR)
            printf("删除�?%d个数据失败\n", j);
        else
            printf("删除�?%d个数据的值为: %d\n", j, e);
    }
    printf("依次输出L的元�?: ");
    ListTraverse(L);

    j = 5;
    ListDelete(&L, j, &e);
    printf("删除�?%d个元素的值为: %d\n", j, e);

    printf("依次输出L的元�?: ");
    ListTraverse(L);

    SqList Lb; // 构造一个有10个数的顺序线性表Lb
    i = InitList(&Lb);
    for (j = 6; j <= 15; j++)
        i = ListInsert(&Lb, 1, j);

    unionL(&L, Lb);

    printf("依次输出合并后L的元素?: ");
    ListTraverse(L);

    return 0;
}

void visit(ElemType c)
{
    printf("%d ", c);
}

/* 将A和B顺序表合并 */
void unionL(SqList * La, SqList Lb)
{
    int La_len, Lb_len, i;
    ElemType e;
    La_len = ListLength(*La);
    Lb_len = ListLength(Lb);
    for (i = 1; i <= Lb.length; i++)
    {
        GetElem(Lb, i, &e);
        if (!LocateElem(*La, e))
            ListInsert(La, ++La_len, e);
    }
}

/* 初始化顺序线性表 */
Status InitList(SqList * L)
{
    L->length = 0;
    return OK;
}

/* 初始条件：顺序线性表L已存�? */
/* 操作结果：若L为空表，则返回TRUE，否则返回FALSE */
Status ListEmpty(SqList L)
{
    if (L.length == 0)
        return TRUE;
    else
        return FALSE;
}


/* 初始条件：顺序线性表L已存�? */
/* 操作结果：将L重置为空�? */
Status ClearList(SqList * L)
{
    L->length = 0;
    return OK;
}


/* 初始条件：顺序线性表L已存�? */
/* 操作结果：返回L中数据元素个�? */
Status GetElem(SqList L, int i, ElemType * e)
{
    if (L.length < 1 || L.length < i || i < 1)
        return ERROR;
    *e = L.data[i-1];
    return OK;
}

/* 初始条件：顺序线性表L已存�?, 1≤i≤ListLength(L) */
/* 操作结果：在L中第i个位置之前插入新的数据元素e, L的长度加1 */
Status ListInsert(SqList * L, int i, ElemType e)
{
    int n;
    if (L->length == MAXSIZE)
        return ERROR;
    if (i < 1 || i > L->length+1)
        return ERROR;
    if (i <= L->length)
        for (n = L->length-1; n >= i-1; n--)
            L->data[n+1] = L->data[n];
    L->data[i-1] = e;
    L->length++;
    return OK;
}


/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(SqList * L, int i, ElemType * e)
{
    if (L->length == 0)
        return ERROR;
    if (i < 1 || i > L->length)
        return ERROR;
    *e = L->data[i-1];
    if (i < L->length)
        while (i <= L->length)
        {
            L->data[i-1] = L->data[i];
            i++;
        }
    L->length--;
    return OK;
}

/* 初始条件：顺序线性表L已存�? */
/* 操作结果：依次对L的每个数据元素输�? */
Status ListTraverse(SqList L)
{
    int i;
    for (i = 0; i < L.length; i++)
        visit(L.data[i]);
    printf("\n");
    return OK;
}

/* 初始条件：顺序线性表L已存�? */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序, 若这样的数据元素不存在，则返回值为0 */
int LocateElem(SqList L, ElemType e)
{
    int i;
    if (L.length < 1)
        return ERROR;
    for (i = 0; i < L.length; i++)
        if (L.data[i] == e)
            break;
    if (i == L.length)
        return 0;
    else
        return (i+1);
}

/* 返回L顺序表的长度 */
int ListLength(SqList L)
{
    return L.length;
}
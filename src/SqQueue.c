#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20
#define OK      1
#define ERROR   0
#define TRUE    1
#define FALSE   0

typedef int Status;
typedef int ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int front;   // 头指针
    int rear;    // 尾指针
} SqQueue;

Status InitQueue(SqQueue ** Q);
Status QueueEmpty(SqQueue * Q);
Status EnQueue(SqQueue * Q, ElemType e);
Status DeQueue(SqQueue * Q, ElemType * e);
Status QueueTraverse(SqQueue * Q);
Status QueueClear(SqQueue * Q);
Status QueueDestory(SqQueue * Q);
int QueueLength(SqQueue * Q);
void visit(ElemType e);

int main(void)
{
    SqQueue * Q;
    ElemType e;

    if (InitQueue(&Q))
        printf("初始化队列成功！\n");
	printf("\n");

	for (int i = 0; i < 10; i++)
		EnQueue(Q, i);
	printf("入队后队内元素为: ");
	QueueTraverse(Q);
	printf("此时队列的长度为: %d\n", QueueLength(Q));
	printf("\n");

	printf("开始出队...");
	DeQueue(Q, &e);
	printf("出队的元素为: %d\n", e);
	printf("此时队列的元素为: ");
	QueueTraverse(Q);
	printf("此时的队列的长度为: %d\n", QueueLength(Q));
	printf("此时队列是否为空(1:是 0:否): %d\n", QueueEmpty(Q));
	printf("\n");

	printf("开始清空队列...\n");
	QueueClear(Q);
	printf("此时队列是否为空(1:是 0:否): %d\n", QueueEmpty(Q));
	printf("\n");

	printf("开始销毁队列...\n");
	QueueDestory(Q);
	printf("销毁队列成功！");

    return 0;
}

/* 初始化队列 */
Status InitQueue(SqQueue ** Q)
{
    *Q = (SqQueue *) malloc(sizeof(SqQueue));
    (*Q)->front = 0;
    (*Q)->rear = 0;
    return OK;
}

/* 判断队列是否为空 */
Status QueueEmpty(SqQueue * Q)
{
    if (Q->front == Q->rear)
        return TRUE;
    else
        return FALSE;
}

/* 入队操作 */
Status EnQueue(SqQueue * Q, ElemType e)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front)
        return ERROR;
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}

/* 出队操作 */
Status DeQueue(SqQueue * Q, ElemType * e)
{
    if (Q->front == Q->rear)
        return ERROR;
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return OK;
}

/* 遍历队列 */
Status QueueTraverse(SqQueue * Q)
{
    int i = Q->front;
    while (i != Q->rear)
    {
        visit(Q->data[i]);
        i = (i + 1) % MAXSIZE;
    }
    printf("\n");
    return OK;
}
/* 清空队列 */
Status QueueClear(SqQueue * Q)
{
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

/* 销毁队列 */
Status QueueDestory(SqQueue * Q)
{
    free(Q);
    return OK;
}

/* 获取队列的长度 */
int QueueLength(SqQueue * Q)
{
    return ((Q->rear - Q->front + MAXSIZE) % MAXSIZE);
}

/* 打印元素 */
void visit(ElemType e)
{
    printf("%d ", e);
}

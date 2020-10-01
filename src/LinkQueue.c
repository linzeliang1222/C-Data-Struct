#include <stdio.h>
#include <stdlib.h>

#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0

typedef int Status;
typedef int ElemType;

typedef struct QNode
{
    ElemType data;
    struct QNode * next;
} QNode, * QueuePtr;
typedef struct
{
    QueuePtr front;
    QueuePtr rear;
} LinkQueue, * LinkQueuePtr;

Status InitQueue(LinkQueuePtr * Q);
Status EnQueue(LinkQueuePtr * Q, ElemType e);
Status DeQueue(LinkQueuePtr * Q, ElemType * e);
Status QueueTraverse(LinkQueuePtr Q);
Status QueueClear(LinkQueuePtr * Q);
Status QueueDestory(LinkQueuePtr * Q);
Status QueueEmpty(LinkQueuePtr Q);
int QueueLength(LinkQueuePtr Q);
void visit(ElemType e);

int main(void)
{
    LinkQueuePtr Q;
    ElemType e;

    if (InitQueue(&Q))
        printf("初始化队列成功！\n");
	printf("\n");

	for (int i = 0; i < 10; i++)
		EnQueue(&Q, i);
	printf("入队后队内元素为: ");
	QueueTraverse(Q);
	printf("此时队列的长度为: %d\n", QueueLength(Q));
	printf("\n");

	printf("开始出队...\n");
	DeQueue(&Q, &e);
	printf("出队的元素为: %d\n", e);
	printf("此时队列的元素为: ");
	QueueTraverse(Q);
	printf("此时的队列的长度为: %d\n", QueueLength(Q));
	printf("此时队列是否为空(1:是 0:否): %d\n", QueueEmpty(Q));
	printf("\n");

	printf("开始清空队列...\n");
	QueueClear(&Q);
	printf("此时队列是否为空(1:是 0:否): %d\n", QueueEmpty(Q));
	printf("\n");

	printf("开始销毁队列...\n");
	QueueDestory(&Q);
	printf("销毁队列成功！");

    return 0;
}

/* 初始化链栈 */
Status InitQueue(LinkQueuePtr * Q)
{
    *Q = (LinkQueuePtr) malloc(sizeof(LinkQueue));
    (*Q)->front = (QueuePtr) malloc(sizeof(QNode));
    (*Q)->rear = (*Q)->front;
    (*Q)->front->next = NULL;
    return OK;
}

/* 元素入队 */
Status EnQueue(LinkQueuePtr * Q, ElemType e)
{
    LinkQueuePtr p;
    QueuePtr q;
    p = *Q;
    q = (QueuePtr) malloc(sizeof(QNode));
    if (!q)
        return ERROR;
    q->data = e;
    q->next = NULL;
    p->rear->next = q;
    p->rear = q;
    return OK;
}

/* 元素出队 */
Status DeQueue(LinkQueuePtr * Q, ElemType * e)
{
    LinkQueuePtr p;
    QueuePtr q;
    p = *Q;
    q = p->front->next;
    if (p->front == p->rear)
        return ERROR;
    *e = q->data;
    p->front->next = q->next;
    if (p->rear == q) // 如果删除的是最后一个元素，那么两个指针应该相等
        p->rear = p->front;
    free(q);
    return OK;
}

/* 遍历队列 */
Status QueueTraverse(LinkQueuePtr Q)
{
    QueuePtr p;
    p = Q->front->next;
    while (p)
    {
        visit(p->data);
		p = p->next;
    }
    printf("\n");
    return OK;
}

/* 清空队列 */
Status QueueClear(LinkQueuePtr * Q)
{
    LinkQueuePtr p;
    QueuePtr q;
    p = *Q;
    q = p->front->next;
    while (q)
    {
        p->front = q->next;
        free(q);
        q = p->front;
    }
    p->rear = p->front = NULL;
    return OK;
}

/* 销毁队列 */
Status QueueDestory(LinkQueuePtr * Q)
{
	if ((*Q)->front != (*Q)->rear)
		QueueClear(Q);
    free(*Q);
    return OK;
}

/* 判断队列是否为空 */
Status QueueEmpty(LinkQueuePtr Q)
{
    if (Q->front == Q->rear)
        return TRUE;
    else
        return FALSE;
    return OK;
}

/* 获取队列的长度 */
int QueueLength(LinkQueuePtr Q)
{
   int count = 0;
   QueuePtr p;
   p = Q->front;
   while (p != Q->rear)
   {
       count++;
       p = p->next;
   }
   return count;
}

/* 打印元素 */
void visit(ElemType e)
{
    printf("%d ", e);
}

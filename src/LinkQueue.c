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
        printf("��ʼ�����гɹ���\n");
	printf("\n");

	for (int i = 0; i < 10; i++)
		EnQueue(&Q, i);
	printf("��Ӻ����Ԫ��Ϊ: ");
	QueueTraverse(Q);
	printf("��ʱ���еĳ���Ϊ: %d\n", QueueLength(Q));
	printf("\n");

	printf("��ʼ����...\n");
	DeQueue(&Q, &e);
	printf("���ӵ�Ԫ��Ϊ: %d\n", e);
	printf("��ʱ���е�Ԫ��Ϊ: ");
	QueueTraverse(Q);
	printf("��ʱ�Ķ��еĳ���Ϊ: %d\n", QueueLength(Q));
	printf("��ʱ�����Ƿ�Ϊ��(1:�� 0:��): %d\n", QueueEmpty(Q));
	printf("\n");

	printf("��ʼ��ն���...\n");
	QueueClear(&Q);
	printf("��ʱ�����Ƿ�Ϊ��(1:�� 0:��): %d\n", QueueEmpty(Q));
	printf("\n");

	printf("��ʼ���ٶ���...\n");
	QueueDestory(&Q);
	printf("���ٶ��гɹ���");

    return 0;
}

/* ��ʼ����ջ */
Status InitQueue(LinkQueuePtr * Q)
{
    *Q = (LinkQueuePtr) malloc(sizeof(LinkQueue));
    (*Q)->front = (QueuePtr) malloc(sizeof(QNode));
    (*Q)->rear = (*Q)->front;
    (*Q)->front->next = NULL;
    return OK;
}

/* Ԫ����� */
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

/* Ԫ�س��� */
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
    if (p->rear == q) // ���ɾ���������һ��Ԫ�أ���ô����ָ��Ӧ�����
        p->rear = p->front;
    free(q);
    return OK;
}

/* �������� */
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

/* ��ն��� */
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

/* ���ٶ��� */
Status QueueDestory(LinkQueuePtr * Q)
{
	if ((*Q)->front != (*Q)->rear)
		QueueClear(Q);
    free(*Q);
    return OK;
}

/* �ж϶����Ƿ�Ϊ�� */
Status QueueEmpty(LinkQueuePtr Q)
{
    if (Q->front == Q->rear)
        return TRUE;
    else
        return FALSE;
    return OK;
}

/* ��ȡ���еĳ��� */
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

/* ��ӡԪ�� */
void visit(ElemType e)
{
    printf("%d ", e);
}

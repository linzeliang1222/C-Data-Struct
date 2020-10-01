#include <stdio.h>
#include <stdlib.h>

#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0

typedef int ElemType;
typedef int Status;

typedef struct BiTNode
{
	ElemType data;
	struct BiTNode * lchild;
	struct BiTNode * rchild;
} BiTNode, * BiTPtr;

typedef struct QNode
{
	BiTPtr data;
	struct QNode * next;
} QNode, * QueuePtr;
typedef struct
{
	QueuePtr front;
	QueuePtr rear;
} LinkQueue, * LinkQueuePtr;

Status InitTree(BiTPtr * T);
Status CreateBiTree(BiTPtr * T);
int DeepCount(BiTPtr T);
int Root(BiTPtr T);
int LeafCount(BiTPtr T);
Status PreOrderTraverse(BiTPtr T);
Status InOrderTraverse(BiTPtr);
Status PostOrderTraverse(BiTPtr T);
Status LayerOrderTraverse(BiTPtr T);
Status InitQueue(LinkQueuePtr * Q);
Status EnQueue(LinkQueuePtr * Q, BiTPtr T);
BiTPtr DeQueue(LinkQueuePtr * Q);
Status LayerOrderTraverse(BiTPtr T);

int main(void)
{
	BiTPtr T;
	
	CreateBiTree(&T);
	printf("%d\n", Root(T));
	printf("%d\n",DeepCount(T));
	printf("%d\n",LeafCount(T));
	LayerOrderTraverse(T);
	
	return 0;
}

Status InitTree(BiTPtr * T)
{
	*T = NULL;
	return OK;
}

Status CreateBiTree(BiTPtr * T)
{
	static int temp = 1;
	if (temp)
	{
		printf("请输入根节点: ");
		temp = 0;
	}
	int ch;
	scanf("%d", &ch);
	if (ch == -1)
	{
		*T = NULL;
		return OK;
	}
	else
	{
		*T = (BiTPtr) malloc(sizeof(BiTNode));
		if (*T == NULL)
			return ERROR;
		else
		{
			(*T)->data = ch;
			printf("请输入%d的左子节点: ", ch);
			CreateBiTree(&((*T)->lchild));
			printf("请输入%d的右子节点: ", ch);
			CreateBiTree(&((*T)->rchild));
		}
	}
	return OK;
}

int DeepCount(BiTPtr T)
{
	if (T == NULL)
		return 0;
	int leftDeep = DeepCount(T->lchild);
	int rightDeep = DeepCount(T->rchild);
	return leftDeep >= rightDeep ? (leftDeep + 1) : (rightDeep + 1);
}

int Root(BiTPtr T)
{
	return T->data;
}

int LeafCount(BiTPtr T)
{
	static int count;
	if (T != NULL)
	{
		if (T->lchild == NULL && T->rchild == NULL)
		{
			count++;
			return 0;
		}
		LeafCount(T->lchild);
		LeafCount(T->rchild);
	}
	return count;
}

Status PreOrderTraverse(BiTPtr T)
{
	if (T == NULL)
		return ERROR;
	printf("%d ", T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
	return OK;
}

Status InOrderTraverse(BiTPtr T)
{
	if (T == NULL)
		return ERROR;
	InOrderTraverse(T->lchild);
	printf("%d ", T->data);
	InOrderTraverse(T->rchild);
	return OK;
}

Status PostOrderTraverse(BiTPtr T)
{
	if (T == NULL)
		return ERROR;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%d ", T->data);
	return OK;
}

Status LayerOrderTraverse(BiTPtr T)
{
	LinkQueuePtr Q;
	BiTPtr p;
	InitQueue(&Q);
	if (T == NULL)
		return ERROR;
	EnQueue(&Q, T);
	while (p = DeQueue(&Q))
	{
		printf("%d ", p->data);
		if (p->lchild)
			EnQueue(&Q, p->lchild);
		if (p->rchild)
			EnQueue(&Q, p->rchild);
	}
	printf("\n");
	return OK;
}


Status InitQueue(LinkQueuePtr * Q)
{
	*Q = (LinkQueuePtr) malloc(sizeof(LinkQueue));
	(*Q)->front = (QueuePtr) malloc(sizeof(QNode));
	(*Q)->rear = (*Q)->front;
	(*Q)->front->next = NULL;
	return OK;
}

Status EnQueue(LinkQueuePtr * Q, BiTPtr T)
{
	LinkQueuePtr p;
	QueuePtr q;
	p = *Q;
	q = (QueuePtr) malloc(sizeof(QNode));
	if (!q)
		return ERROR;
	q->data = T;
	p->rear->next = q;
	q->next = NULL;
	p->rear = q;
	return OK;
}

BiTPtr DeQueue(LinkQueuePtr * Q)
{
	LinkQueuePtr p;
	QueuePtr q;
	BiTPtr r;
	p = *Q;
	q = p->front->next;
	if (p->front == p->rear)
		return NULL;
	r = q->data;
	p->front->next = q->next;
	if (q == p->rear)
		p->rear = p->front;
	free(q);
	return r;
}

Status DestoryQueue(LinkQueuePtr * Q)
{
	
	return OK;
}
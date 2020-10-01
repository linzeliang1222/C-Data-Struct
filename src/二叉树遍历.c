#include <stdio.h>
#include <stdlib.h>

#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0

typedef char ElemType;
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
Status PreOrderTraverse(BiTPtr T);
Status InOrderTraverse(BiTPtr);
Status PostOrderTraverse(BiTPtr T);
Status LayerOrderTraverse(BiTPtr T);
Status InitQueue(LinkQueuePtr * Q);
Status EnQueue(LinkQueuePtr * Q, BiTPtr T);
BiTPtr DeQueue(LinkQueuePtr * Q);
Status LayerOrderTraverse(BiTPtr T);
int DeepCount(BiTPtr T);
int Root(BiTPtr T);
int LeafCount(BiTPtr T);
int TotalNodeCount(BiTPtr T);

int main(void)
{
	BiTPtr T;
	
	CreateBiTree(&T);
	printf("\n二叉树创建完成...\n");
	printf("\n二叉树的深度为: %d\n", DeepCount(T));
	printf("\n二叉树的根节点为: %c\n", Root(T));
	printf("\n二叉树的叶子结点数为: %d\n", LeafCount(T));
	printf("\n二叉树的总结点数为: %d\n", TotalNodeCount(T));
	printf("\n后序遍历二叉树如下: ");
	PostOrderTraverse(T);
	
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
		printf("请输入根节点(#代表无结点): ");
		temp = 0;
	}
	char ch;
	scanf("%c", &ch);
	getchar();
	if (ch == '#')
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
			printf("请输入%c的左子节点: ", ch);
			CreateBiTree(&((*T)->lchild));
			printf("请输入%c的右子节点: ", ch);
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

int TotalNodeCount(BiTPtr T)
{
	static int count = 0;
	if (T != NULL)
	{
		count++;
		TotalNodeCount(T->lchild);
		TotalNodeCount(T->rchild);
	}
	return count;
}

Status PreOrderTraverse(BiTPtr T)
{
	if (T == NULL)
		return ERROR;
	printf("%c ", T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
	return OK;
}

Status InOrderTraverse(BiTPtr T)
{
	if (T == NULL)
		return ERROR;
	InOrderTraverse(T->lchild);
	printf("%c ", T->data);
	InOrderTraverse(T->rchild);
	return OK;
}

Status PostOrderTraverse(BiTPtr T)
{
	if (T == NULL)
		return ERROR;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c ", T->data);
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
		printf("%c ", p->data);
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
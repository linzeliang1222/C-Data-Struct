/* ������������Ĵ洢�ṹ */
#include <stdio.h>

#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0

typedef int Status;
typedef char TElemType;

/* �������Ķ��������洢�ṹ���� */
typedef enum {Link, Thread} PointerTag; // Link = 0��ʾָ�����Һ��ӵ�ָ�� Thread = 1��ʾָ��ǰ�����̵�����

typedef struct BiThrTree
{
    TElemType data;                      // �������
    struct BiThrTree * lchild, * rchild; // ���Һ���ָ��
    PointerTag LTag;                     // ���ұ�־
    PointerTag RTag;
} BiThrNode, * BiThrTree;

BiThrTree pre; // ȫ�ֱ�����ʼ��ָ��ոշ��ʹ��Ľ��

void InThreading(BiThrTree p);
Status InOrderTraverse_Thr(BiThrTree T);

int main(void)
{
    return 0;
}

/* ��������������������� */
void InThreading(BiThrTree p)
{
    if (p)
    {
        InThreading(p->lchild);
        if (!p->lchild)
        {
            p->LTag = Thread;   // ǰ������
            p->lchild = pre;    // ����ָ��ָ��ǰ��
        }
        if (!pre->rchild)
        {
            pre->RTag = Thread; // �������
            pre->rchild = p;
        }
        pre = p;                // ����preָ��p��ǰ��
        InThreading(p->rchild); // �ݹ�������������
    }
}

/* Tָ��ͷ��㣬ͷ�������lchildָ����ڵ㣬ͷ�������rchildָ��������������һ����㡣��������������������ʾ�Ķ�����T */
Status InOrderTraverse_Thr(BiThrTree T)
{
    BiThrTree p;
    p = T->lchild; // pָ����ڵ�
    while (p != T) // ���������������ʱ��p == T
    {
        while (p->LTag == Link) //��LTag����0ʱѭ�����������еĵ�һ�����
            p = p->lchild;
        printf("%c\n", p->data);
        while (p->RTag == Thread && p->rchild != T)
        {
            p = p->rchild;
            printf("%c", p->data);
        }
        p = p->rchild; // p��������������
    }
    return OK;
}
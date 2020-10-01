/* 线索二叉链表的存储结构 */
#include <stdio.h>

#define OK    1
#define ERROR 0
#define TRUE  1
#define FALSE 0

typedef int Status;
typedef char TElemType;

/* 二叉树的二叉线索存储结构定义 */
typedef enum {Link, Thread} PointerTag; // Link = 0表示指向左右孩子的指针 Thread = 1表示指向前驱或后继的线索

typedef struct BiThrTree
{
    TElemType data;                      // 结点数据
    struct BiThrTree * lchild, * rchild; // 左右孩子指针
    PointerTag LTag;                     // 左右标志
    PointerTag RTag;
} BiThrNode, * BiThrTree;

BiThrTree pre; // 全局变量，始终指向刚刚访问过的结点

void InThreading(BiThrTree p);
Status InOrderTraverse_Thr(BiThrTree T);

int main(void)
{
    return 0;
}

/* 中序遍历进行中序线索化 */
void InThreading(BiThrTree p)
{
    if (p)
    {
        InThreading(p->lchild);
        if (!p->lchild)
        {
            p->LTag = Thread;   // 前驱线索
            p->lchild = pre;    // 左孩子指针指向前驱
        }
        if (!pre->rchild)
        {
            pre->RTag = Thread; // 后继线索
            pre->rchild = p;
        }
        pre = p;                // 保持pre指向p的前驱
        InThreading(p->rchild); // 递归右子树线索化
    }
}

/* T指向头结点，头结点左链lchild指向根节点，头结点右链rchild指向中序遍历的最后一个结点。中序遍历二叉线索链表表示的二叉树T */
Status InOrderTraverse_Thr(BiThrTree T)
{
    BiThrTree p;
    p = T->lchild; // p指向根节点
    while (p != T) // 空树或遍历结束的时，p == T
    {
        while (p->LTag == Link) //当LTag等于0时循环到中序序列的第一个结点
            p = p->lchild;
        printf("%c\n", p->data);
        while (p->RTag == Thread && p->rchild != T)
        {
            p = p->rchild;
            printf("%c", p->data);
        }
        p = p->rchild; // p进至其右子树根
    }
    return OK;
}
#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 100

typedef int TElemType; // 树结点结构数据类型

typedef struct CTNode  // 孩子结点
{
    int child;
    struct CTNode * next;
} * ChildPtr;
typedef struct         // 表头结构
{
    TElemType data;
    ChildPtr firstchild;
} CTBox;
typedef struct         // 树结构
{
    CTBox nodes[MAX_TREE_SIZE]; // 结点数组
    int r;                      // 根的位置
    int n;                      // 结点数
} CTree;

int main(void)
{
    return 0;
}
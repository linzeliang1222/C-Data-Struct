#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 100

typedef int TElemType; // 树结点结构数据类型

/* 树的孩子兄弟表示法结构定义 */
typedef struct CSNode
{
    TElemType data;
    struct CSNode * firstchild, * rightsib, * parent;
} CSNode, * CSTree;

int main(void)
{
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 100

typedef int TElemType; // �����ṹ��������

/* ���ĺ����ֵܱ�ʾ���ṹ���� */
typedef struct CSNode
{
    TElemType data;
    struct CSNode * firstchild, * rightsib, * parent;
} CSNode, * CSTree;

int main(void)
{
    return 0;
}
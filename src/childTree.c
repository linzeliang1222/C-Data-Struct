#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_SIZE 100

typedef int TElemType; // �����ṹ��������

typedef struct CTNode  // ���ӽ��
{
    int child;
    struct CTNode * next;
} * ChildPtr;
typedef struct         // ��ͷ�ṹ
{
    TElemType data;
    ChildPtr firstchild;
} CTBox;
typedef struct         // ���ṹ
{
    CTBox nodes[MAX_TREE_SIZE]; // �������
    int r;                      // ����λ��
    int n;                      // �����
} CTree;

int main(void)
{
    return 0;
}
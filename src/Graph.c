#include <stdio.h>
#define MAXVEX 100

typedef char VertexType;    // 顶点类型
typedef int EdgeType;       // 边上的权值

typedef struct EdgeNode     // 边表结点
{
    int adjvex;             // 邻接点域存储该顶点对应的下标
    EdgeType weight;        // 存储权值
    struct EdgeNode * next; // 链域，指向下一个邻接点
}EdgeNode;
typedef struct VertexNode
{
    VertexType data;        // 顶点域，存储顶点信息
    EdgeNode * firstedge;   //便表头指针
}VertexNode, AdjList[MAXVEX];
typedef struct
{
    AdjList adjlist;
    int numVertexes, numEdges; //图中当前顶点数和边数
}GraphAdjList;

int main(void)
{
    return 0;
}

void CreateALGraph(GraphAdjList * G)
{
    int i, j, k;
    EdgeNode * e;
    
}
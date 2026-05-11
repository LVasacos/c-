/*
邻接表2

试在邻接表存储结构上实现图的基本操作 del_vertex，相关定义如下：

typedef int VertexType;

typedef enum{
    DG, UDG
}GraphType;

typedef struct ArcNode{
    int adjvex;
    InfoPtr *info;
    struct ArcNode *nextarc;
}ArcNode;

typedef struct VNode{
    VertexType data;
    ArcNode *firstarc;
}VNode;
typedef struct{
    VNode vertex[MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphType type;
}ListGraph;

int locate_vertex(ListGraph *G, VertexType v); //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool del_vertex(ListGraph *G, VertexType v); //删除顶点 v
当成功删除顶点或边时，函数返回true，否则（如顶点或边不存在、删除边时顶点v或w不存在）返回false。
*/

#include <stdio.h>
#include <stdlib.h>
#include "graph.h" //请勿删除，否则检查不通过
#define MAX_SIZE 50

bool del_vertex(ListGraph *G, VertexType v) {
    if (G == NULL) return false;
    int loc = locate_vertex(G, v);
    if (loc == -1) return false;

    // 1. 释放该顶点发出的所有边（出边）
    ArcNode *p = G->vertex[loc].firstarc;
    while (p != NULL) {
        ArcNode *tmp = p;
        p = p->nextarc;
        free(tmp);
        G->arcnum--; // 如果是无向图，这里先减去一半的计数
    }
    G->vertex[loc].firstarc = NULL;

    // 2. 遍历图中所有其他顶点，删除指向 loc 的边（入边/无向图的对称边）
    for (int i = 0; i < G->vexnum; i++) {
        if (i == loc) continue; // 跳过已清空的被删点

        ArcNode *pre = NULL;
        ArcNode *curr = G->vertex[i].firstarc;
        while (curr != NULL) {
            if (curr->adjvex == loc) {
                // 找到指向 loc 的边，执行删除
                if (pre == NULL) {
                    G->vertex[i].firstarc = curr->nextarc;
                } else {
                    pre->nextarc = curr->nextarc;
                }
                ArcNode *next_node = curr->nextarc;
                free(curr);
                curr = next_node;
                
                // 注意：在无向图中，只需在这里减 arcnum；
                // 在有向图中，入边也算一条弧。
                if (G->type == DG || G->type == UDG) G->arcnum--; 
                // 无向图的 arcnum 已经在第一步或这里的对称位置处理过了，
                // 建议根据你教材对 arcnum 的定义微调计数逻辑
            } else {
                pre = curr;
                curr = curr->nextarc;
            }
        }
    }

    // 3. 删除顶点表中的该项，后续顶点前移
    for (int j = loc + 1; j < G->vexnum; j++) {
        G->vertex[j - 1] = G->vertex[j];
    }
    G->vexnum--;

    // 4. 更新所有边表中的 adjvex 索引
    for (int i = 0; i < G->vexnum; i++) {
        ArcNode *curr = G->vertex[i].firstarc;
        while (curr != NULL) {
            if (curr->adjvex > loc) {
                curr->adjvex--;
            }
            curr = curr->nextarc;
        }
    }

    return true;
}
/*
邻接表1

试在邻接表存储结构上实现图的基本操作 insert_vertex 和 insert_arc，相关定义如下：

typedef int VertexType;

typedef enum{
    DG, UDG
}GraphType;

typedef struct ArcNode
{
    int adjvex;
    InfoPtr *info;
    struct ArcNode *nextarc;

}ArcNode; //弧

typedef struct VNode
{
    VertexType data;
    ArcNode *firstarc;
}VNode;  //顶点
typedef struct
{
    VNode vertex[MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphType type;
}ListGraph; 

int locate_vertex(ListGraph* G, VertexType v); //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool insert_vertex(ListGraph *G, VertexType v);
bool insert_arc(ListGraph *G, VertexType v, VertexType w);
当成功插入顶点或边时，函数返回true，否则（如顶点或边已存在、插入边时顶点v或w不存在）返回false。
*/
#include <stdio.h>
#include <stdlib.h>
#include "graph.h" //请勿删除，否则检查不通过

bool insert_vertex(ListGraph *G, VertexType v){
    if(G==NULL){return false;} //是否有效
    if(G->vexnum==MAX_VERTEX_NUM){return false;}//是否超限
    for(int i=0;i<G->vexnum;i++){
        if(G->vertex[i].data==v){return false;} //是否已经有
    }
    G->vertex[G->vexnum].data=v;
    G->vertex[G->vexnum].firstarc=NULL;
    G->vexnum++;
    return true;
}


bool insert_arc(ListGraph *G, VertexType v, VertexType w){
    if(G==NULL){return false;}
    int i=locate_vertex(G, v);
    int j=locate_vertex(G, w);
    if(i==-1 || j==-1){return false;}//检查顶点是否存在
    ArcNode *p = G->vertex[i].firstarc;
    while(p!=NULL){//检查弧是否已经存在
        if(p->adjvex==j){return false;}
        p=p->nextarc;
    }
    ArcNode* temp=(ArcNode*)malloc(sizeof(ArcNode));//分配内存并检查
    if(temp==NULL){return false;}
    temp->nextarc=NULL; //初始化
    temp->adjvex=j; //连接尾
    G->vertex[i].firstarc=temp;
    if(G->type==UDG){  //检查是不是无向图
        ArcNode* temp2=(ArcNode*)malloc(sizeof(ArcNode));//分配内存并检查
        if(temp2==NULL){return false;}
        temp2->nextarc=NULL; //初始化
        temp2->adjvex=i; //连接头
        G->vertex[j].firstarc=temp2;
    }
    

    G->arcnum++;
    return true;
}
/*
ArcNode存adjvex（弧尾顶点在顶点数组中的位置），info（权重），nextarc（同一首顶点的下一个弧的指针）
VNode存data（值），firstarc（顶点的第一个弧的指针）
ListGraph存vertex（顶点数组）等
其中弧需要malloc，顶点不用，因为顶点已经规定了多少（数组），是静态的，而弧是动态的。
*/
/*
邻接矩阵

试在邻接矩阵存储结构上实现图的基本操作 matrix_insert_vertex 和matrix_insert_arc，相关定义如下：

typedef int VertexType;

typedef enum{
    DG, UDG
}GraphType;

typedef struct{
    VertexType vertex[MAX_VERTEX_NUM]; //顶点向量
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //邻接矩阵
    int vexnum, arcnum;   //图的当前顶点数和弧数
    GraphType type;     //图的种类标志
}MatrixGraph;

int matrix_locate_vertex(MatrixGraph *MG, VertexType vex); //返回顶点 v 在vertex数组中的下标，如果v不存在，返回-1
bool matrix_insert_vertex(MatrixGraph *G, VertexType v);
bool matrix_insert_arc(MatrixGraph *G, VertexType v, VertexType w);
当成功插入顶点或边时，函数返回true，否则（如顶点或边已存在、插入边时顶点v或w不存在）返回false。
*/

#include <stdio.h>
#include "graph.h" // 请不要删除，否则检查不通过

bool matrix_insert_vertex(MatrixGraph *G, VertexType v){
    if(G==NULL){return false;} //是否无效值
    if (G->vexnum>=MAX_VERTEX_NUM){return false;} //是否超出
    for(int i=0;i<G->vexnum;i++){
        if(G->vertex[i]==v){return false;} //是否已经有
    }
    G->vertex[G->vexnum]=v;
    for(int i=0; i<=G->vexnum;i++){  //初始化邻接矩阵
        G->arcs[i][G->vexnum]=0;
        G->arcs[G->vexnum][i]=0;
    }
    (G->vexnum)++; //更新数据
    return true;


}

bool matrix_insert_arc(MatrixGraph *G, VertexType v, VertexType w){
    if(G==NULL){return false;} //是否无效值
    if (G->arcnum>=(MAX_VERTEX_NUM * MAX_VERTEX_NUM)){return false;} //是否超出
    int i=matrix_locate_vertex(G, v);
    if(i==-1){return false;}
    int j=matrix_locate_vertex(G, w);
    if(j==-1){return false;}       //检查是否存在顶点
    if(G->arcs[i][j]==1){return false;}//检查边是否存在
    else{
        if(G->type==DG){ G->arcs[i][j]=1;}
        else{ G->arcs[i][j]=1; G->arcs[j][i]=1;}
       }
    (G->arcnum++);
    return true;
}

/*
反思：
1.插入一个顶点后，要初始化它在邻接矩阵上的弧，防止垃圾影响；
2.要考虑到有向图（DG）和无向图(UDG)。
*/
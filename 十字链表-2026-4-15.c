/*十字链表

十字链表相关定义如下：

typedef int ElemType;

// 非零元素结点结构
typedef struct OLNode
{
    int row,col;
    ElemType value;
    struct OLNode *right,*down;
}OLNode,*OLink;

// 十字链表结构
typedef struct
{
    OLink *rowhead,*colhead;
    int rows,cols,nums;
}CrossList, *PCrossList;
1）实现十字链表的初始化操作：

 int init_cross_list(PCrossList L, const ElemType *A, int m, int n);
其中 L 指向 CrossList 结构，且各成员已被初始化为0；
A 为 ElemType 类型数组中第一个元素的地址，元素的个数为 m×n 个，按行优先存储（即A[0] 为十字链表第1行第1列的元素；
A[1] 为第1行第2列的元素，A[n] 为第2行第1列的元素，A[n+1] 为第2行第2个元素）；
m 表示十字链表的行数，n 表示十字链表的列数。
init_cross_list 函数将 ElemType 数组中非0元素保存到十字链表中，函数返回非 0 元素的个数。

2）实现十字链表的删除操作：

 int del_cross_list(PCrossList L, ElemType k);
其中 L 指向 要处理的 CrossList 结构，k 为要删除的元素；
del_cross_list 函数删除十字链表中所有值为 k 的结点，并返回删除结点的个数。*/




#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "crosslist.h"

int init_cross_list(PCrossList L, const ElemType *A, int m,int n){
    if(!L || !A || m<=0 || n<=0){return false;}
    L->nums=0;
    OLink temp;
    L->rows=m;
    L->cols=n;
    L->rowhead = (OLink*)malloc((m + 1) * sizeof(OLink));
    L->colhead = (OLink*)malloc((n + 1) * sizeof(OLink));
    if(!L->colhead || !L->rowhead){return false;}
    for(int i=0;i<=m;i++){L->rowhead[i]=NULL;}
    for(int i=0;i<=n;i++){L->colhead[i]=NULL;} // 初始化指针列表
    for(int k=0;k<m*n;k++){
        if(A[k]!=0){temp=(OLink)malloc(sizeof(OLNode));
            if(!temp){return L->nums;}
            L->nums++;
            temp->row=k/n+1;
            temp->col=k%n+1;
            temp->value=A[k];
            if(L->rowhead[temp->row]==NULL){
                L->rowhead[temp->row]=temp;
                temp->right=NULL;  //留意这一行
            }
            else{
                OLink current;
                current=L->rowhead[temp->row];
                while(current->right!=NULL){current=current->right;}
                current->right=temp;
                temp->right=NULL;
            }
            if(L->colhead[temp->col]==NULL){
                L->colhead[temp->col]=temp;
                temp->down=NULL;
            }
            else{
                OLink current;
                current=L->colhead[temp->col];
                while(current->down!=NULL){current=current->down;}
                current->down=temp;
                temp->down=NULL;
            }

    }   
}
return L->nums;
}   


    
int del_cross_list(PCrossList L, ElemType k){
    if(!L){return 0;}  // 修正：k是int，不能!k
    OLink temp, pre_row, pre_col;
    int num=0;
    
    for(int i=1; i<=L->rows; i++){  // 修正：从1开始，不是0
        pre_row = NULL;              // 修正：每行重新初始化
        temp = L->rowhead[i];

        while(temp != NULL){
            if(temp->value == k){
                // 从行链表中删除
                if(pre_row == NULL){
                    L->rowhead[i] = temp->right;
                } else {
                    pre_row->right = temp->right;
                }
                
                // 从列链表中删除
                pre_col = NULL;
                OLink col_temp = L->colhead[temp->col];
                while(col_temp != NULL && col_temp != temp){
                    pre_col = col_temp;
                    col_temp = col_temp->down;
                }
                if(col_temp == temp){
                    if(pre_col == NULL){
                        L->colhead[temp->col] = temp->down;
                    } else {
                        pre_col->down = temp->down;
                    }
                }
                
                OLink next = temp->right;  // 保存下一个节点
                free(temp);                 // 释放内存
                temp = next;
                num++;
                L->nums--;                  // 更新非零元个数
                continue;
            }
            pre_row = temp;
            temp = temp->right;
        }
    }
    return num;
}
    

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
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    while(k<=m*n-1){
        if(A[k]!=0){
            temp=(OLink*)malloc(sizeof(OLNode));
            if(temp==NULL){
                free(temp);
                return false;
            }
            temp->value=A[k];
            if(L->rowhead[0]==NULL &&L->colhead[0]==NULL){
                L->rowhead[0]=temp;
                L->colhead[0]=temp;
            }
            if(temp->row==n){
                j=1;
                i++;
                temp->row=i;
                temp->col=j;
                current=L->rowhead;
                int r=1;
                while(r<temp->row-1){
                    current=current->down;
                    r++;
                }
                current->down=temp;
                current=temp;
                if(L->cols<n){L->cols++;}
            }
            else{
                j++;
                temp->row=i;
                temp->col=j;
                current->right=temp;
                current=temp;
                L->rows++;
            }
            k++;
            L->nums++;

        }
        else{
            k++;
        }

    } 
  return L->nums;
}


int del_cross_list(PCrossList L, ElemType k){
    

}
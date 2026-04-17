/*
矩阵加法

实现三元组表示的两个稀疏矩阵的加法。相关定义如下：

#define MAXSIZE 100          //假设非零元个数的最大值为100
typedef struct {
    int i,j;									//非零元的行下标和列下标，i 和 j 从 1 开始计数，与数学中矩阵元素的编号一致
    ElemType e;						//非零元的值
}Triple;

typedef struct {
    Triple data[MAXSIZE];			// 非零元三元组表
    int    m, n, len;							// 矩阵的行数、列数和非零元个数
}TSMatrix;
在三元组中，i 和 j 从 1 开始计数，与数学中矩阵元素的编号一致
矩阵加法函数的原型为：

bool add_matrix(const TSMatrix *pM, const TSMatrix *pN, TSMatrix *pQ);
pM, pN, pQ 分别指向三个矩阵，当 pM 和 pN 两个矩阵不可加时，函数返回 false，否则函数返回 true，且 pQ 指向两个矩阵的和。
*/




#include <stdio.h>
#include <stdlib.h>
#include "tsmatrix.h"

bool add_matrix(const TSMatrix *pM, const TSMatrix *pN, TSMatrix *pQ){
    if(pM==NULL || pN==NULL){return false;}
    if(pM->m<0 ||pM->n<0 ||pN->m<0 ||pN->n<0 ||pM->len<0 ||pN->len<0 ){return false;}
    if(pM->len < 0 || pM->len > MAXSIZE || pN->len < 0 || pN->len > MAXSIZE) {return false;}
    if(pM->m!=pN->m || pM->n!=pN->n){return false;}
    
    pQ->m=pM->m;
    pQ->n=pM->n;
    pQ->len=0;  //初始化
    int o=0,p=0,k=0;
    while(o<=pM->len-1 && p<=pN->len-1){
        if(pM->data[o].i<pN->data[p].i ||( (pM->data[o].i==pN->data[p].i)&&(pM->data[o].j<pN->data[p].j))){ //M当前标记的节点在N之前
            pQ->data[k].e=pM->data[o].e;
            pQ->data[k].i=pM->data[o].i;
            pQ->data[k].j=pM->data[o].j;
            pQ->len++;
            o++;
            k++;
        }
        else if(pM->data[o].i>pN->data[p].i ||( (pM->data[o].i==pN->data[p].i)&&(pM->data[o].j>pN->data[p].j))){ //M当前标记的节点在N之后
            pQ->data[k].e=pN->data[p].e;
            pQ->data[k].i=pN->data[p].i;
            pQ->data[k].j=pN->data[p].j;
            pQ->len++;
            k++;
            p++;
        }
        else{ //M当前标记的节点和N重合
            if(pM->data[o].e+pN->data[p].e==0){o++; p++;} //和为0则跳过，不计入
            else{
                 pQ->data[k].e=pM->data[o].e+pN->data[p].e ; 
                 pQ->data[k].i=pN->data[p].i;
                 pQ->data[k].j=pN->data[p].j;
                 pQ->len++;
                 k++;
                 p++;
                 o++;
            }
        }  
    }
    if(o>pM->len-1 && p<=pN->len-1){ //N还没录完M就没了
        while(p<=pN->len-1){  //直接将N剩余的录入
            pQ->data[k].e=pN->data[p].e;
            pQ->data[k].i=pN->data[p].i;
            pQ->data[k].j=pN->data[p].j;
            k++;
            p++;
            pQ->len++;
        }
    }    
    else if(o<=pM->len-1 && p>pN->len-1){//M还没录完N就没了
        while(o<=pM->len-1){ //直接将M剩余的录入
            pQ->data[k].e=pM->data[o].e;
            pQ->data[k].i=pM->data[o].i;
            pQ->data[k].j=pM->data[o].j;
            k++;
            o++;
            pQ->len++;
        }
    }    
    
    

        
        
    return true;
    
    }
/*
1.认知错误，稀疏矩阵不是所有元都需要存储一个值，依据题意只存储非零元，否则浪费空间；已经声明了需要返回的矩阵不需要malloc，已经申请好了空间。pQ是二级指针/创建并返回才需要；
2.注意处理每一个需要自增的变量
3.区分"->"和"." , 指针才用箭头
4.指针才可以为NULL,数组结构什么的不行
*/
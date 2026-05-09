/*
先序遍历

已知二叉树按照二叉链表方式存储，利用栈的基本操作写出先序遍历非递归形式的算法：

void pre_order(BiTree root);
在遍历过程中，pre_order函数需要调用 visit_node 函数来实现对结点的访问，该函数声明如下：

void visit_node(BiTNode *node);
二叉树的相关定义如下：

typedef int DataType;

typedef struct Node{
    DataType data;
    struct Node* left;
    struct Node* right;
}BiTNode, *BiTree;
遍历所使用栈的相关操作如下：

#define Stack_Size 50
typedef BiTNode* ElemType;
typedef struct{
    ElemType elem[Stack_Size];
    int top;
}Stack;

void init_stack(Stack *S); // 初始化栈
bool push(Stack* S, ElemType x); //x 入栈
bool pop(Stack* S, ElemType *px); //出栈，元素保存到px所指的单元，函数返回true,栈为空时返回 false
bool top(Stack* S, ElemType *px); //获取栈顶元素，将其保存到px所指的单元，函数返回true，栈满时返回 false
bool is_empty(Stack* S);  // 栈为空时返回 true，否则返回 false
*/

/*
初始思路：要求采用非递归，那就采用双指针，一个pre指针一个temp指针，如果temp指向的结点没有子结点，说明达到这一分支的栈底，可是如何排序？
如果采用双层循环，外层持续向left分支传递，内层持续向right分支传递呢？
事实上不行，那就先处理每一个节点，将每一个节点入栈，一旦达到一个分支的栈底（if），就弹出一个节点，它是记录栈内最深的节点，
然后右转，将其变为下一个循环的父节点，之后下一个循环继续遍历，同时记录，这样就不需要双指针，只需要采用两个while循环，条件为
当前节点不为NULL且栈不空 和 当前节点不为NULL
*/

#include <stdlib.h>
#include <stdio.h>
#include "bitree.h" //请不要删除，否则检查不通过

void pre_order(BiTree root){
    if(root==NULL){return;}
    Stack q;
    init_stack(&q);//初始化记录栈
    BiTNode* temp=root;
    while(temp!=NULL || !is_empty(&q)){
        while(temp!=NULL ){
            visit_node(temp);
            push(&q,temp);
            temp=temp->left;
        }
        pop(&q,&temp);
        temp=temp->right;
    }

}
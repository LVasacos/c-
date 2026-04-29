/*
路径

假设二叉树采用二叉链表方式存储， root指向根结点，node 指向二叉树中的一个结点，编写函数 path，计算root到 node 之间的路径，（该路径包括root结点和 node 结点）。path 函数声明如下：

bool path(BiTNode* root, BiTNode* node, Stack* s);
其中，root指向二叉树的根结点，node指向二叉树中的另一结点，s 为已经初始化好的栈，该栈用来保存函数所计算的路径，如正确找出路径，则函数返回 true，此时root在栈底，node在栈顶；如未找到，则函数返回 false, 二叉树的相关定义如下：

typedef int DataType;

typedef struct Node{
    DataType data;
    struct Node* left;
    struct Node* right;
}BiTNode, *BiTree;
栈的相关定义及操作如下：

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
思路：从根节点开始前序遍历，同时入栈，如果找不到就出栈重复
会不会太耗性能？重复出入栈太耗时间了？
*/
#include <stdlib.h>
#include <stdio.h>
#include "bitree.h" //请不要删除，否则检查不通过


bool find_path(BiTNode* root, BiTNode* node, Stack* s){ //找路函数
    if(root==NULL || node==NULL){return false;}   //检查  
    push(s,root);  //根入栈
    if(root==node){return true;} //找到就返回true
    if(find_path(root->left,  node, s)){return true;} //递归，找到就返回true ————>短路剪枝，节省时间&空间
    if(find_path(root->right,  node, s)){return true;}
    
    BiTNode* temp;//声明临时变量，没找到就出栈，递归可以出栈本身的栈项  
    pop(s, &temp);
    return false;


}

bool path(BiTNode* root, BiTNode* node, Stack* s){//引用找路函数
    if(root==NULL || node==NULL){return false;} //检测 
    init_stack(s); //初始化栈，清空
    return find_path(root, node, s);
    
}
/*
树转二叉树

使用队列，编写transfrom函数，将普通树转换成对应的二叉树。二叉树的相关定义如下：

typedef int DataType;

typedef struct Node{
    DataType data;
    struct Node* left;
    struct Node* right;
}BiTNode, *BiTree;
普通树节点的定义如下：

#define MAX_CHILDREN_NUM 5
struct _CSNode
{
    DataType data;
    struct _CSNode *children[MAX_CHILDREN_NUM];
};
typedef struct _CSNode CSNode;
其中，子树的根节点的指针存放在children数组的前k个元素中，即如果children[i]的值为NULL，而children[i-1]不为NULL，则表明该结点只有i棵子树，子树根结点分别保存在children[0]至children[i-1]中。

队列相关定义及操作如下：

struct __Queue
{
    int i, j; //指向数组内元素的游标
    void **array;
};
typedef struct __Queue Queue;

Queue* create_queue(); //创建队列
bool is_empty_queue(Queue *tree); //队为空返回true,不为空时返回false
void* del_queue(Queue *tree); //结点指针出队
void add_queue(Queue *tree, void *node); //结点指针入队
void free_queue(Queue *tree); //释放队列
transform函数定义如下：

BiTNode* transform(CSNode *root);
其中 root 为普通树的根结点，函数返回该树对应二叉树的根结点。
*/

/*
思路：队列读取普通树，原来的兄弟节点放右边，父子节点放左边。
先入队根节点，出队一个节点，将所有它的children放在该节点的左节点，上一个节点的右节点，然后把所有children入队，最后出队一个节点，以此循环。

*/

#include <stdlib.h>
#include <stdio.h>
#include "bitree.h" //请不要删除，否则检查不通过
#include <stdbool.h>

BiTNode* transform(CSNode *root){
    BiTNode* biRoot = (BiTNode*)malloc(sizeof(BiTNode)); //申请二叉树根节点空间
    if (biRoot == NULL) return NULL;   //初始化二叉树根节点
    biRoot->data = root->data;
    biRoot->left = NULL;
    biRoot->right = NULL;
    
    Queue* q=create_queue(); //创建队列
    if(q==NULL){return false;}
    

    typedef struct {//创建配对结构体，方便寻找父节点;
        CSNode* csNode;   // 原树节点
        BiTNode* biNode;  // 对应的二叉树节点
    } NodePair; 
    
    struct NodePair* pair = malloc(sizeof(struct NodePair));//录入根节点结构
    pair->csNode=root;
    pair->biNode=biRoot;
    add_queue(q, pair); //原始树根节点结构入队
    
    while(!is_empty_queue(q)){  //开始处理每一个队列的元素
        void* p =del_queue(q); //出队
        int k=0;
        BiTNode* temp=p->biNode;
        while(p->csNode->children[k]!=NULL && k<=MAX_CHILDREN_NUM-1){
            if(k==0){temp->left=p->csNode->children[k];temp=temp->left;}
            if(k>0){temp->right=p->csNode->children[k];temp=temp->right;}
            struct NodePair* pair = malloc(sizeof(struct NodePair));
            pair->csNode=p->csNode->children[k];
            pair->biNode=temp;
            add_queue(q, pair);
            k++;
        }
    }
 


    
    


}
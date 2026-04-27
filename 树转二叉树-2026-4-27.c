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
先入队根节点结构，出队一个结构，将所有它的原树的children数据录入新创建的二叉树节点，右串联到上一个节点的左节点，然后把所有children结构入队，以此循环。

*/

#include <stdlib.h>
#include <stdio.h>
#include "bitree.h" //请不要删除，否则检查不通过
#include <stdbool.h>

typedef struct {//创建配对结构体，方便寻找父节点;
        CSNode* csNode;   // 原树节点
        BiTNode* biNode;  // 对应的二叉树节点
    } NodePair; 
    

BiTNode* transform(CSNode *root){
    if(root==NULL){return NULL;}
    BiTNode* biRoot = (BiTNode*)malloc(sizeof(BiTNode)); //申请二叉树根节点空间
    if (biRoot == NULL) return NULL;   //初始化二叉树根节点
    biRoot->data = root->data;
    biRoot->left = NULL;
    biRoot->right = NULL;
    
    Queue* q=create_queue(); //创建队列
    if(q==NULL){return NULL;}
    
    NodePair* rootpair = malloc(sizeof(NodePair));//录入根节点结构
    rootpair->csNode=root;
    rootpair->biNode=biRoot;
    add_queue(q, rootpair); //原始树根节点结构入队
    
    while(!is_empty_queue(q)){  //开始处理每一个队列的元素
        NodePair* p = (NodePair*)del_queue(q); //出队并且强制转换为NodePair类型，方便下面temp的赋值
        int k=0;
        BiTNode* temp=p->biNode;
        while(k<MAX_CHILDREN_NUM && p->csNode->children[k]!=NULL){ //注意顺序
            BiTNode* newNode = (BiTNode*)malloc(sizeof(BiTNode)); //不能直接将原树的节点给二叉树，得创建新的二叉树节点并赋值
            newNode->data=p->csNode->children[k]->data;
            newNode->left=NULL;
            newNode->right=NULL;

            if(k==0){temp->left=newNode; temp=temp->left;}
            if(k>0){temp->right=newNode; temp=temp->right;}
            NodePair* childpair = malloc(sizeof(NodePair));
            childpair->csNode=p->csNode->children[k];
            childpair->biNode=temp;
            add_queue(q, childpair);
            k++;

        }
        free(p);//清理内存
    }

    free_queue(q);
    return biRoot;
 
}

/*实际上使用双队列会更加简洁，同步存储原树节点和对应的二叉树节点，操作时进行同步操作*/
/*
二叉树的存储结构如下：

typedef struct _btree_node {
char tag; //二叉树结点的字符标签
struct _btree_node *left, *right; //左子树和右子树
} btree_node, *btree;
二、任务描述
请设计一个算法，实现一棵二叉树的镜像翻转。

三、编码约束
算法函数原型：
btree mirror(btree tree);
功能：生成二叉树tree的镜像二叉树，返回镜像二叉树的根结点指针。
参数：tree是指向源二叉树根结点的指针
返回值：指向二叉树tree的镜像二叉树根结点的指针

编码约束
时间复杂度：无特别要求
空间复杂度：无特别要求
*/
typedef struct _btree_node {
char tag; //二叉树结点的字符标签
struct _btree_node *left, *right; //左子树和右子树
} btree_node, *btree;

btree mirror(btree tree){  //这种算法是直接修改原树，破坏了原树，不符合“生成”的语义；
    if(tree==NULL){return NULL;}
    btree temp;
    temp=tree->left;
    tree->left=tree->right;
    tree->right=temp;
    mirror(tree->right);
    mirror(tree->left);
    return tree; 


}


/*答案*/
btree mirror(btree tree){  
    if(tree==NULL){return NULL;}
    btree new_tree=(btree)malloc(sizeof(btree_node));
    if(!new_tree){free(new_tree);return NULL;}
    new_tree->tag=tree->tag;
    new_tree->right= mirror(tree->left);
    new_tree->left=mirror(tree->right);
    return new_tree; 


}

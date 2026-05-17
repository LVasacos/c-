/*
假设以带头结点的循环链表表示队列，并且只设一个指针指向队尾元素结点（注意不设头指针），请完成下列任务：

队列初始化，成功返回真，否则返回假： bool init_queue(LinkQueue *LQ);

入队列，成功返回真，否则返回假： bool enter_queue(LinkQueue *LQ, ElemType x);

出队列，成功返回真，且*x为出队的值，否则返回假 bool leave_queue(LinkQueue *LQ, ElemType *x);

补全下面代码：
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct _QueueNode {
    ElemType data;            // 数据域
    struct _QueueNode *next;  // 指针域
} LinkQueueNode, *LinkQueue;

bool init_queue(LinkQueue *LQ)
{
    // 为头结点分配内存
    *LQ = (LinkQueue)malloc(sizeof(LinkQueueNode));
    if (*LQ == NULL) {
        return false; // 内存分配失败
    }

    (*LQ)->next = *LQ; 
    return true;
}

bool enter_queue(LinkQueue *LQ, ElemType x)
{
    // 创建新结点
    LinkQueueNode *p = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    if (p == NULL) {
        return false; // 内存分配失败
    }
    p->data = x;

    // 将新结点插入到队尾（即头结点之前，原尾结点之后）
    p->next = (*LQ)->next; // 新结点的 next 指向头结点
    (*LQ)->next = p;       // 原尾结点的 next 指向新结点
    *LQ = p;               // LQ 指针更新，指向新的队尾元素

    return true;
}


bool leave_queue(LinkQueue *LQ, ElemType *x)
{
    // 如果 LQ->next == LQ，说明队列中只有头结点，队列为空
    if (*LQ == (*LQ)->next) {
        return false; 
    }

    // 头结点是 (*LQ)->next，队头元素结点是头结点的下一个结点
    LinkQueueNode *head = (*LQ)->next;
    LinkQueueNode *p = head->next; 

    // 取出队头元素的值
    *x = p->data;

    // 从链表中删除该结点
    head->next = p->next;
    if (p == *LQ) {
        *LQ = head;
    }

    // 释放结点内存
    free(p);
    return true;
}
/*
队列先进先出，越新入队的排越后，越老的离头结点越近，出队先出队头；
一般循环链表：队尾->头结点（可能有头指针，头结点不存数据）->队头->......
这道题中*LQ指向尾指针，其next指向头结点；
空表时，让队尾指针临时指向头结点，这时表里只有头结点一个结点，为其分配空间即初始化；
为空时插入，*LQ指向插入结点，使其为队尾，其next指向头结点，头结点接上插入结点构成循环，这样，最老的结点就是头结点的下一个，即队头；
不为空时插入，不能破坏队头和头结点的连接，所以在队尾后插入新结点，将*LQ更新到新的结点将其变为新队尾，然后处理连接问题（先想好在哪插，再处理连接）
*/
/*这里是标记空链表并且原地两两合并，属于分治法变种，相对于经典分治法更加复杂，也更难维护，相对地，时间复杂度更低。
经典分治法采用的递归，不管是否为空，显然更加简洁优雅。
*/

/*
给你一个链表数组，每个链表都已经按升序排列。
请你将所有链表合并到一个升序链表中，返回合并后的链表。
示例 1：

输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6
示例 2：

输入：lists = []
输出：[]
示例 3：

输入：lists = [[]]
输出：[]
 
提示：

k == lists.length
0 <= k <= 10^4
0 <= lists[i].length <= 500
-10^4 <= lists[i][j] <= 10^4
lists[i] 按 升序 排列
lists[i].length 的总和不超过 10^4
*/




/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

// 合并两个有序链表
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;
    
    struct ListNode dummy;
    dummy.next = NULL;
    struct ListNode* tail = &dummy;
    
    while (l1 && l2) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    
    tail->next = (l1 != NULL) ? l1 : l2;
    return dummy.next;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if(lists==NULL || listsSize<=0){return NULL;}  //检查：改为 <= 0
    
    int k=0,i=0,empty_num=0;
    int empty[listsSize]; //创建数组标记空链表的下标（此时 listsSize > 0，安全）
    for(i=0;i<listsSize;i++){//初始化标记链表
        empty[i]=0;
    }
    for(k=0;k<listsSize;k++){//遍历所有的链表，找出空链表并标记
        if(lists[k]==NULL){
            empty[k]=1;
            empty_num+=1;
        }
    }
    if(empty_num==listsSize){return NULL;}//全部为空则返回空表
    if(listsSize==1){//只有一个链表直接返回
        return lists[0];
    }
    /*以上已经完成了所有准备工作，接下来就是比较所有数的大小并且加入新链表（可以借助队列），但是该如何节省空间和时间呢？
    方法1：每次加入链表就遍历链表比较大小，然后执行插入链表，显然低效；
    方法2：记录所有数、排序，再一个个加入链表，操作较方法1更为简单，边界问题也更好处理，但是感觉不能很好地利用小链表本身就是升序排列的特点；
    方法3：将k个数组合并，传统方法插入新数时要遍历一整个链表，时间复杂度为O(N²)，如果用二分法的思想呢？合并相邻的两个链表，然后以此类推，每次合并相邻的链表直到剩一个链表，这样的时间复杂度就是O(Nlog k)，其中N为总节点数。
    */
    
    // 方法3实现：原地两两合并，直到只剩一个非空链表
    while (empty_num < listsSize - 1) {  // 当还有多个非空链表时继续
        i = 0;
        while (i < listsSize) {
            // 找第一个非空链表
            while (i < listsSize && empty[i] == 1) {
                i++;
            }
            if (i >= listsSize) break;
            int first = i;
            i++;
            
            // 找第二个非空链表
            while (i < listsSize && empty[i] == 1) {
                i++;
            }
            
            if (i < listsSize) {
                // 找到两个，合并它们
                int second = i;
                lists[first] = mergeTwoLists(lists[first], lists[second]);
                lists[second] = NULL;
                empty[second] = 1;
                empty_num++;
                i++;
            }
            // 如果找不到第二个，first落单，下一轮继续
        }
    }
    
    // 返回最后剩下的非空链表
    for (i = 0; i < listsSize; i++) {
        if (empty[i] == 0) {
            return lists[i];
        }
    }
    
    return NULL;
}
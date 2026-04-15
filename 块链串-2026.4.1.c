/*
块链串

块链串定义如下：

#define BLOCK_SIZE 4    // 可由用户定义的块大小
#define BLS_BLANK '#'   // 用于空白处的补齐字符

typedef struct _block {
    char ch[BLOCK_SIZE];    //块的数据域
    struct _block *next;    //块的指针域
} Block;

typedef struct {
    Block *head;        // 串的头指针
    Block *tail;        // 串的尾指针
    int len;            // 串的当前长度
} BLString;

//字符串初始化函数：
void blstr_init(BLString *T) {
    T->len = 0;
    T->head = NULL;
    T->tail = NULL;
}
这些定义已包含在头文件 dsstring.h 中，请实现块链串的子串查找操作：

bool blstr_substr(BLString src, int pos, int len, BLString *sub);
src为要查找的字符串
pos为子串开始的下标
len为子串的长度
sub在函数调用运行前指向一个已经初始化好的空串，在函数返回时，sub指向串src从第pos个字符起长度为len的子串
函数查找成功返回true，参数不正确返回 false
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dsstring.h"

bool blstr_substr(BLString src, int pos, int len, BLString *sub) {
    if (sub == NULL) {
        return false;
    }
    if (pos < 0) {
        return false;
    }
    if (src.head == NULL) {
        return false;
    }
    if (len == 0) {
        sub->head = NULL;
        sub->tail = NULL;
        sub->len = 0;
        return true;
    }
    if (pos + len > src.len) {
        return false;
    }        //没有自动截断，无法全部读取就一个都不读取了

    sub->head = NULL;
    sub->tail = NULL;
    sub->len = 0;

    Block *temp = src.head;
    int block_pos = 0;
    int remaining = len;
    int offset = 0;

    while (temp != NULL && block_pos + BLOCK_SIZE < pos) {   //这里应是block_pos + BLOCK_SIZE <= pos
        block_pos += BLOCK_SIZE;
        temp = temp->next;
    }

    if (temp == NULL) {
        return false;
    }

    offset = pos - block_pos;

    while (temp != NULL && remaining > 0) {
        int addnum = (remaining <= BLOCK_SIZE - offset) ? remaining : (BLOCK_SIZE - offset);  
        Block *new_block = (Block *)malloc(sizeof(Block));    //动态内存就需要malloc申请内存，比如不确定大小的链表；记得释放内存。 申请Block大小的内存并且强制转换为Block类型。
        if (new_block == NULL) {
            Block *clean = sub->head;
            while (clean != NULL) {
                Block *next = clean->next;
                free(clean);  
                clean = next;  //清理空间不可少
            }
            return false;
        }   

        new_block->next = NULL;
        int j = 0;
        while (j < addnum) {
            new_block->ch[j] = temp->ch[offset + j];
            j++;
        }     //这里思路是：挨个找出本次应该从一个源代码块中录入多少，录入完切换下一个源代码块，很不方便；  正确思路应是：外层控制（remaining<0），内层控制（j<MAX_SIZE）进行填充,同时持续检测offset（偏移），如果顶格则切换下一个源代码块并归零offset。 
        while (j < BLOCK_SIZE) {
            new_block->ch[j] = '#';
            j++;
        }        

        if (sub->head == NULL) {
            sub->head = new_block;
            sub->tail = new_block;
        } else {
            sub->tail->next = new_block;
            sub->tail = new_block;
        }

        temp = temp->next;
        sub->len += addnum;
        remaining -= addnum;
        offset = 0;
    }

    return true;
}

/*正确代码*/

#include <stdlib.h>
#include <string.h>
#include "dsstring.h"

bool blstr_substr(BLString src, int pos, int len, BLString *sub) {
    // 1. 基本合法性检查
    // 如果 sub 指针为空，或者 pos 超过了原串范围，或者长度为负数，返回 false
    if (sub == NULL || pos < 0 || pos >= src.len || len < 0) {
        return false;
    }

    // 2. 自动截断处理：如果要求的长度超过了原串剩余部分，则只取到末尾
    if (pos + len > src.len) {
        len = src.len - pos;
    }

    // 初始化 sub 串
    sub->head = NULL;
    sub->tail = NULL;
    sub->len = 0;

    if (len == 0) return false;

    // 3. 定位起始块
    Block *src_temp = src.head;
    int current_block_start = 0;
    while (src_temp != NULL && current_block_start + BLOCK_SIZE <= pos) {
        current_block_start += BLOCK_SIZE;
        src_temp = src_temp->next;
    }

    if (src_temp == NULL) return false;

    int src_offset = pos - current_block_start;
    int remaining = len;

    // 4. 提取子串
    while (remaining > 0) {
        Block *new_block = (Block *)malloc(sizeof(Block));
        if (new_block == NULL) {
            // 内存分配失败清理
            Block *p = sub->head;
            while (p) { Block *next = p->next; free(p); p = next; }
            return false;
        }
        new_block->next = NULL;

        // 填充块内字符
        for (int j = 0; j < BLOCK_SIZE; j++) {
            if (remaining > 0) {
                // 跨块检查
                if (src_offset >= BLOCK_SIZE) {
                    src_temp = src_temp->next;
                    src_offset = 0;
                }
                
                if (src_temp != NULL) {
                    new_block->ch[j] = src_temp->ch[src_offset];
                    src_offset++;
                    remaining--;
                    sub->len++;
                } else {
                    // 防御性处理：理论上不应到达这里
                    new_block->ch[j] = BLS_BLANK;
                }
            } else {
                // 子串取完，填充占位符
                new_block->ch[j] = BLS_BLANK;
            }
        }

        // 挂载节点
        if (sub->head == NULL) {
            sub->head = new_block;
            sub->tail = new_block;
        } else {
            sub->tail->next = new_block;
            sub->tail = new_block;
        }
    }

    return true;
}


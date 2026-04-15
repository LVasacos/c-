/*栈 后缀表达式计算

请使用已定义好的栈完成后缀表达式计算：
(1)如果是操作数，直接入栈
(2)如果是操作符op，连续出栈两次，得到操作数x 和 y,计算 x op y，并将结果入栈。

后缀表达式示例如下：
9  3  1  -  3  *  +  10  2  /  +9  3  1  -  3  *     10  2  /
13  445  +  51  /  6  -13  445     51  /  6  -
操作数、操作符之间由空格隔开，操作符有 +，-，*, /, %共 5 种符号，所有操作数都为整型。

栈的定义如下：

#define Stack_Size 50
typedef struct{
    ElemType elem[Stack_Size];
    int top;   int最高;
}Stack;   }堆栈;

bool push(Stack* S, ElemType x);bool push(Stack* S, ElemType x)；
bool pop(Stack* S, ElemType *x);bool pop(Stack* S, ElemType *x)；
void init_stack(Stack *S);void init_stack（栈*S）；
其中，栈初始化的实现为：

void init_stack(Stack *S){void init_stack（栈*S）{
    S->top = -1;   S->top = -1；
}
需要完成的函数定义为：int compute_reverse_polish_notation(char *str);

函数接收一个字符指针，该指针指向一个字符串形式的后缀表达式，函数返回该表达式的计算结果。*/


#include <stdio.h>   # include & lt; stdio.h>
#include <stdlib.h>   # include & lt; stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过
#include <ctype.h>   # include & lt; ctype.h>
#include <string.h>
#include <stdbool.h>
int compute_reverse_polish_notation(char *str){
    Stack S;
    init_stack(&S);  //不声明栈变量会报错
    
    
    char *token=strtok(str," ");   //strtok返回的是地址，需要一个指向字符的指针。
    while(token!=NULL){
        if(isdigit(token[0]) || (token[0]=='-' && isdigit(token[1]))){
            int num=atoi(token); //atoi()转换token为数字，另一种类似的如num=num*10+(str-'0')
            push(&S,num);}
       else{
            int x,y,sum;
            pop(&S, &y);
            pop(&S, &x);  //注意取值顺序不能反
            switch(token[0]){
                    case '+':sum=x+y;break;
                    case '-':sum=x-y;break;
                    case '*':sum=x*y;break;
                    case '/':sum=x/y;break;
                    case '%':sum=x%y;break;  //一定记得要break
                }
                push(&S,sum);
         }
         
         token=strtok(NULL," ");  //多次使用strtok时不用在指定目标，但是仍要指定不取的对象
    }
int all;
pop(&S,&all);
return all;  
    
}

/*
原本思路为：遍历str找出不是空格的，放入newstr，然后再遍历运算。
修改思路为：使用strtok()，直接获取数字/符号，处理并更新token。#其基于<string.h>*/

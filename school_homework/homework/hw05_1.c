//栈的实现 数列版本
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 20

typedef struct stack
{
    char store[MAX];
    int top;
    int maxsize;
}stack;
void initstack(stack *s,int maxsize);
bool isempty(stack *s);
bool isfull(stack *s);
int push(stack *s,char c);
int pop(stack *s ,char *c);

int main()
{
    printf("输入字符串：");
    char c;
    stack *s = malloc(sizeof(stack));
    if (s == NULL) {
    printf("内存分配失败！\n");
    return 1;
}
    initstack(s,MAX);
    while((c = getchar()) != '\n')
    {
        push(s,c);
    }
    while(!isempty(s))
    {
        pop(s,&c);
        printf("%c",c);
    }
    free(s);
}
void initstack(stack *s,int maxsize)
{
    s->top = -1;
    s->maxsize = maxsize;
}
bool isempty(stack *s)
{
    return s->top == -1;
}
bool isfull(stack *s)
{
    return s->top == s->maxsize - 1;
}
int push(stack *s,char c)
{
    if(!isfull(s))
    {
        s->store[++s->top] = c;
        return 0;
    }
    else
    {
        return 1;
    }
}
int pop(stack *s ,char *c)
{
    if(!isempty(s))
    {
        *c = s->store[s->top--];
        return 0;
    }
    else
    {
        return 1;
    }
}
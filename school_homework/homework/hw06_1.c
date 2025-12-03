#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct link
{
    int data;
    struct link * next;
}link;
int main()
{

}

void delete_1(link *l,int x)//非递归方法
{
    
    while(l->next!= NULL)
    {
        if(l->next->data == x)
        {
            link *temp = l->next;
            l->next = l->next->next;
            free(temp);
        }
        else
        {
            l = l->next;
        }
    }
}
void delete_2(link *l,int x)//递归方法
{
    if(l->next != NULL)
    {
        if(l->next->data == x)
        {
            link *temp = l->next;
            l->next = l->next->next;
            free(temp);
            delete_2(l,x);
        }
        else
        {
            delete_2(l->next,x);
        }
    }
}
int search(link *l,int k,int size)//size 可以通过调用下面那个函数算出
{
    int far = size - k;
    if(far < 0)
    {
        return 0;//k大于size 必定找不到
    }    
    else
    {
        while(far != 0)
        {
            l = l->next;
            far--;
        }
        printf("%d",&l->data);
        return 1;
    }
}
int sizepointer(link *l)
{
    int size = 0;
    while(l!= NULL)
    {
        size++;
        l = l->next;
    }
    return size;
}

typedef struct link
{
    int data;
    struct link * next;
}link;

typedef struct queue
{
    struct link *front;
    struct link *rear;
    int size;
}queue;

void initialize(queue *p)
{
    p->front = NULL;
    p->rear = NULL;
    p->size = 0;
}

bool is_empty(queue *p)
{
    if(p->front == NULL)
    {
        return true;
    }
    return false;
}

int enqueue(queue *p,int nodedata)//尾插法
{
    link *add = malloc(sizeof(link));
    if(add == NULL)
    {
        return 1;
    }
    add->data = nodedata;
    add->next = NULL;
    if(p->size == 0)
    {
        p->front = add;
        p->rear = add;
    }
    else
    {
        p->rear->next = add;
        p->rear = add;
    }
    p->size++;
    return 0;
}
int dequeue(queue *p)//链式队列从头开始出
{
    if(!is_empty(p))
    {
        int output = p->front->data;
        link *temp = p->front;
        p->front = temp->next;
        p->size--;
        free(temp);
        return output;
    }
    if(p->front == NULL)
    {
        p->rear = NULL;
    }
}
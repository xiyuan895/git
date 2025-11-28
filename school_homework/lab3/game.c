#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_true(int *n,int start,int end,int a_total,int b_total);

int main()
{
    int num;
    scanf("%d",&num);
    int *n = malloc(num * sizeof(int));
    if (n == NULL) // 检查 malloc 是否成功
    {
        printf("内存分配失败\n");
        return 0;
    }
    for(int i = 0;i < num;i++)
    {
        scanf("%d",&n[i]);
    }
    if (is_true(n, 0, num - 1, 0, 0))
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }
    free(n); 
}

bool is_true(int *n, int start, int end, int a_total, int b_total)
{
    // start > end 代表数组为空，结束递归
    if (start > end)
    {
        return a_total >= b_total; 
    }
    //取左or取右
    //选取true的一边，或返回最后的值
    bool pick_left = !is_true(n, start + 1, end, b_total, a_total + n[start]);// a取左边，交换数值位置，进行递归
    bool pick_right = !is_true(n, start, end - 1, b_total, a_total + n[end]);// a取右边，交换数值位置，进行递归

    return pick_left || pick_right;
}

/*bool is_true(int *n,int start,int end,int a_total,int b_total)
{
    if(start == end)
    {
        if (a_total >= b_total)
        {
            return true;
        }
        return false;
    }
    else if(end - start == 1)
    {
        if(n[start] > n[end])
        {
            if(a_total + n[start] >= b_total + n[end])
            {
                return true;
            }
            return false;
        }
        if(n[start] <= n[end])
        {
            if(a_total + n[end] >= b_total + n[start])
            {
                return true;
            }
            return false;
        }
    }
    else if(end > start)
    {
        if(is_true(n,start + 1,end - 1,a_total + n[start],b_total + n[end]))
        {
            return true;
        }
        if(is_true(n,start + 2,end,a_total + n[start],b_total + n[start + 1]))
        {
            return true;
        }
        if(is_true(n,start,end - 2,a_total + n[end],b_total + n[end - 1]))
        {
            return true;
        }
        if(is_true(n,start + 1,end - 1,a_total + n[end],b_total + n[start]))
        {
            return true;
        }
        return false;
    }    
}*/
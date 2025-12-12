#include <stdio.h>

// 函数原型声明(函数的具体实现需要你在文件末尾完成)
void sort_interest(int *interest, int n);

int main() 
{
    int n;
    scanf("%d", &n);
    int interest[100];
    for (int i = 0; i < n; i++) {
        scanf("%d", &interest[i]);
    }
    sort_interest(interest, n);
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", interest[i]);
    }
    printf("\n");
    return 0;
}

// 你需要实现的函数
void sort_interest(int *interest, int n)
{
    for(int i = 0;i < n;i++)
    {
        for(int j = 1;j < n;j++)
        {
            if(interest[j] < interest[j - 1])
            {
                int temp = interest[j];
                interest[j] = interest[j-1];
                interest[j - 1] = temp;
            }
        }
    }
    // 选择排序
    // int max = interest[0];
    // int index = 0;
    // for(int i = 0;i < n;i++)
    // {
    //     for(int j = i;j < n;j++)
    //     {
    //         if(interest[j] >= max)
    //         {
    //             max = interest[j];
    //             index = j;
    //         }
    //     }
    //     int temp = interest[i];
    //     interest[i] = interest[index];
    //     interest[index] = temp; 
    // }
}

//在此处，我使用冒泡排序
//老师还推荐了使用其他的选择排序和插入排序，课后实现
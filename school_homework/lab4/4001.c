#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_help(int i,int j);
int main()
{
    int num;
    int a[20][5] = {0};
    scanf("%d",&num);
    int time[num];
    for(int i = 0;i < num;i++)
    {
        scanf("%d",&time[i]);
    }
    for(int k = 0;k < num;k++)
    {
        bool has_find = false;
        for(int i = 0;i< 20;i++)
        {
            for(int j = 0;j< 5;j++)
            {
                if(a[i][j] == 0 && (5-j) >= time[k])
                {
                    int count = 0;
                    has_find = true;
                    for (int q = 0; q < time[k]; q++) { // 分配连续座位
                        a[i][j + q] = 1;
                        print_help(i, j + q);
                        if(q != time[k] - 1)
                        {
                            printf(" ");
                        }
                    }
                    break;
                }
            }
            if(has_find)
            {
                break;
            }
        }
        if(!has_find)
        {
            int count = 0;
            for(int i = 0;i<20;i++)
            {
                for(int j = 0;j < 5;j++)
                {
                    if(a[i][j] == 0)
                    {
                        a[i][j] = 1;
                        print_help(i,j);
                        count++;
                        if(count != time[k])
                        {
                            printf(" ");
                        }
                    }
                if (count == time[k])
                {
                    break;
                }
                }
                if (count == time[k])
                {
                    break;
                }
            }
        }
        printf("\n");
    }
}
void print_help(int i,int j)
{
    switch (j)
    {
    case 0:
        printf("%dA",i+1);
        break;
    case 1:
        printf("%dB",i+1);
        break;
    case 2:
        printf("%dC",i+1);
        break;
    case 3:
        printf("%dD",i+1);
        break;
    case 4:
        printf("%dF",i+1);
        break;
    default:
        break;
    }
}

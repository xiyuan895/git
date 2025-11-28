#include <stdio.h>
#define MAX 40
float average(int score[],int index);
int stu_num_pass_ave(int score[],float ave,int index);
int main()
{
    int score[MAX] = {0};
    for(int i = 0;i < MAX;i++)
    {
        if(scanf("%d",&score[i]) == 1)
        {
            if (score[i] < 0)
            {
                int num = stu_num_pass_ave(score,average(score,i),i);
                printf("%d",num);
            }
        }
    }
}
float average(int score[],int index)
{
    int total = 0;
    for(int j = 0;j < index;j++)
    {
        total += score[j];
    }
    float ave = total / (float)index;
    return ave;
}
int stu_num_pass_ave(int score[],float ave,int index)
{
    int num = 0;
    for(int i = 0;i< index;i++)
    {
        if((float)score[i] > ave)
        {
            num += 1;
        }
    }
    return num;
}
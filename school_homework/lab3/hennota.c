#include <stdio.h>

int main()
{
    char a = 'A';
    char b = 'B';
    char c = 'C';
    int num;
    scanf("%d",&num);
    hennota(num,a,c,b);
}
void hennota(int num,char source,char end,char help)
{
    if(num > 0)
    {
        hennota(num - 1,source,help,end);
        printf("Move disk from %c to %c\n",source,end,help);
        hennota(num - 1,help,end,source);
    }
}

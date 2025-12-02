#include <stdio.h>
int count(n);
int main()
{
    int n;
    scanf("%d",&n);
    int step = count(n);
    printf("%d\n",step);
} 
int count(n)
{
    if(n == 1)
    {
        return 0;
    }
    else if(n % 2 == 0)
    {
        return 1 + count(n/2);
    }
    else if(n % 2 == 1)
    {
        return 1 + count(n*3 + 1);
    }
}
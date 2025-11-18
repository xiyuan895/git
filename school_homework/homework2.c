#include <stdio.h>
int my_max(int a,int b);
int gongbeishu(int a,int b);
int my_pow(n,k);
int main()
{
    int a,b;
    printf("enter the number\n");
    while (scanf("%d %d",&a,&b) != 2||a*b <= 0)
    {
        printf("invalid enter!\n");
    }//这里解决了输入的问题，方便起见，我们直接要求输入正整数
    int max = my_max(a,b);
    printf("%d\n",max);//这里是返回最大值
    int gbs = gongbeishu(a,b);
    printf("%d\n",gbs);//穷举法求出最小公倍数
    int pow_k_time = my_pow(a,b);
    printf("%d\n",pow_k_time);// 迭代求n的k次方
}
int my_max(int a,int b)
{
    if (a >= b)
        return a;
    else
        return b;
}
int gongbeishu(int a,int b)
{
    for(int i = my_max(a,b);i <= a*b;i++)
    {
        if (i % a == 0 && i % b == 0)
            return i;
    }
    return a*b;
}
int my_pow(n,k)
{
    if(k == 0)
    return 1;
    return my_pow(n,k-1)*n; 
}
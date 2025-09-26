#include <stdio.h>
#include <math.h>

int main()
{
    int number;
    printf("enter the number\n");
    scanf("%d",&number);
    if(number < 0)
    {
        printf("%i\n",(-1)*number);
    }
    else
    {
        printf("%i\n",number);
    }

}
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


#define MAX 100
int calculate(int num[2],char symbol);

int main()
{
    char c;//获取输入
    char buffer[MAX] = {0};
    int index = 0;
    int num[2] ={0};//只使用大小为二的整数数组，用来记录前一数字与后一数字
    int i = 0;
    char symbol;
    while((c = getchar()) != '=')
    {
        if (isdigit(c))//判断是否为数字
        {
            buffer[index] = c;
            index ++;
        }
        else if (index > 0)//若不为数字，则判断是否为有效字符，并重置index
        {
            buffer[index] = '\0';
            num[i] = atoi(buffer);//用atoi函数直接转化字符为数字
            index = 0;
            i++;
            if (i > 1)
            {
            num[0] = calculate(num,symbol);
            i = 1;
            }
            if (c == '+' || c == '-' || c == '*' || c == '/')
            {
                symbol = c;
            }
            else
            {
                printf("错误的运算符:%c\n", c);
                return 0;
            }
        }
        else//防止有非法字符在运算符之后出现
        {
            printf("错误的运算符:%c",c);
            return 0;
        }
    }
   if (index > 0)//单独处理最后一个数字
    {
        buffer[index] = '\0';
        num[1] = atoi(buffer);
        num[0] = calculate(num,symbol);

        // 执行最后一次运算
       
    }
    printf("%d\n", num[0]);
    return 0;
}
int calculate(int num[2],char symbol)//该函数将计算步骤分离
{
     switch (symbol)
        {
            case '+':
                num[0] = num[0] + num[1];
                break;
            case '-':
                num[0] = num[0] - num[1];
                break;
            case '*':
                num[0] = num[0] * num[1];
                break;
            case '/':
                if (num[1] == 0)
                {
                    printf("division by zero!");
                    break;
                }
                num[0] = num[0] / num[1];
                break;
            default:
                printf("invalid symbol %c", symbol);
                break;
        }
        return num[0];
}
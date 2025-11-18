#include <stdio.h>
#include <stdbool.h>
bool is_special_year(int year);//判断某年是否为润年
void rest_work(int day_count);//传入总天数，从而判断是休息还是工作
bool check(int year,int month,int day);//检查输入是否合法
int special_year[12] = {31,29,31,30,31,30,31,31,30,31,30,31};// 闰年的每月天数
int normal_year[12] = {31,28,31,30,31,30,31,31,30,31,30,31};// 平年的每月天数
#define SPECIAL 366//闰年一年的总天数
#define NORMAL 365//平年一年的总天数
int main()
{
    int year,month,day;
    if(scanf("%4d-%2d-%2d",&year,&month,&day) != 3)//输入
    {
        printf("Invalid input\n");
        return 0;
    }
    if(!check(year,month,day))
    {
        printf("Invalid input\n");
        return 0;
    }//合法性检查
    int day_count = distance(year,month,day);//计算总天数
    rest_work(day_count);//判断工作休息
    return 0;
}
bool is_special_year(int year)
{
    if (year % 400 == 0)
    {
        return true;
    }
    else
    {
        if (year % 4 == 0 && year % 100 != 0)
        {
            return true;
        }
    }
    return false;// 不是闰年
}
int distance(int year,int month,int day)
{
    int start_year = 1990;
    int start_month = 1;
    int start_day = 1;
    int distance = 0;
    for(;start_year < year;start_year++)
    {
        if (is_special_year(start_year))
        {
            distance += SPECIAL;
        }
        else
        distance += NORMAL;
    }
    for (;start_month < month;start_month++)
    {
        if(is_special_year(start_year))
        {
            distance += special_year[start_month - 1];
        }
    }
    distance += day;
    return distance;
}
void rest_work(int day_count)
{
    int rest = day_count % 5;
    switch (rest)
    {
    case 1:
    case 2:
    case 3:
        printf("working\n");
        break;
    
    case 0:
    case 4:
        printf("rest\n");
    }
}
bool check(int year,int month,int day)
{
    if (year < 1990|| month > 12 || month < 1 || day > 31)
    return false;
    else
    {
        if(is_special_year(year))
        {
            if(day > special_year[month - 1])
            return false;
        }
        else
        {
            if(day > normal_year[month - 1])
            return false;
        }
    }
    return true;
}
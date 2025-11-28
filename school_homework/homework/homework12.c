#include <stdio.h>
#include <stdlib.h>
int main()
{
    int total = 0;
    int school_num;
    int student_num;
    printf("输入学校与学生的数目：");
    scanf("%d %d",&school_num,&student_num);
    int a[school_num];
    int b[student_num];
    printf("学校的预估分数线：");
    for(int i = 0;i < school_num;i++)
    {
        scanf("%d",&a[i]);
    }
    printf("输入学生的估分：");
    for(int i = 0;i < student_num;i++)
    {
        scanf("%d",&b[i]);
    }
    for(int i = 0;i < student_num;i++)
    {
        total += binary_search(a,0,school_num - 1,b[i]);
    }
    printf("%d",total);
}
int binary_search(int a[],int left,int right,int b)
{
    int min = 0;
    int middle = (left + right)/2;
    if(left == right)
    {
        return abs(a[left] - b);
    }
    if(a[middle] == b)
    {
        return 0;
    }
    else
    {
        min = my_min(binary_search(a,left,middle,b),abs(a[left] - b),binary_search(a,middle,right,b));
        return min;
    }
    
    // if(b >= a[middle])
    // {
    //     if(b < a[(middle + right)/2])
    //     {
    //         return my_min(binary_search(a,middle,(3 * middle + right)/4,b),abs(a[middle] - b),binary_search(a,(3*middle + right)/2,(middle + right)/2,b));
    //     }
    //     else
    //     {
    //         return my_min(binary_search(a,(middle + right)/2,(middle + 3*right)/4,b),abs(a[middle] - b),binary_search(a,(middle + 3*right)/4,right,b));
    //     }
    // }
    // else
    // {
    //     if(b > a[(middle + left)/2])
    //     {
    //         return my_min(binary_search(a,(middle + left)/2,(3*middle + left)/2,b),abs(a[middle] - b),binary_search(a,(3*middle + left)/2,middle,b));
    //     }
    //     else
    //     {
    //         return my_min(binary_search(a,left,(3*middle + left)/2,b),abs(a[middle] - b),binary_search(a,(3*middle + left)/2,(middle + right)/2,b));
    //     }
    // }
    // else
    // {
    //     return my_min(binary_search(a,left,(middle + left)/2,b),abs(a[middle] - b),binary_search(a,(middle + right)/2,right,b));
    // }
}
int my_min(int a,int b,int c)
{
    int min;
    min = a <= b? a : b;
    min = min <= c? min : c;
    return min;
}
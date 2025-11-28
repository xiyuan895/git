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
float average(int score[],int index)//计算平均数
{
    int total = 0;
    for(int j = 0;j < index;j++)
    {
        total += score[j];
    }
    float ave = total / (float)index;
    return ave;
}
int stu_num_pass_ave(int score[],float ave,int index)//计算通过的学生数
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
#include <string.h>
int main()
{
    char char_day[7][10] = {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};
    char enter[10] = {0};
    scanf("%s",enter);
    int day = check_day(char_day,enter);
    if(day != -1)
    {
        printf("%d",day);
    }
}
int check_day(char day[][10],char enter[])
{
    char (*row_pointer)[10] = day;
    for(int i = 0;i < 7;i++)
    {
        if(strcmp(row_pointer[i],enter) == 0)
        {
            return i ;
        }
    }
    return -1;
}

typedef struct student
{
    char *name;
    char *sex;
    BIRTHDAY date;
    JOB job;
}STUDENT;
typedef struct birthday
{
    int year;
    int month;
    int day;
}BIRTHDAY;
typedef struct job
{
    char *college;
    char *professional_tital;
    char *position;
}JOB;
int main()
{
    STUDENT worker[5];
    int index = 0;
    int max = 0;
    for(int i = 0; i < 5;i++)
    {
        worker[i].name = (char *)malloc(50 * sizeof(char));
        if(worker[i].name == NULL)
        {
            free_pointer(worker);
            return 1;
        }
        worker[i].sex = (char *)malloc(10 * sizeof(char));
        if(worker[i].sex == NULL)
        {
            free_pointer(worker);
            return 1;
        }
        worker[i].job.college = (char *)malloc( 50 * sizeof(char));
        if(worker[i].job.college == NULL)
        {
            free_pointer(worker);
            return 1;
        } 
        worker[i].job.position = (char *)malloc( 50 * sizeof(char));
        if(worker[i].job.position == NULL)
        {
            free_pointer(worker);
            return 1;
        } 
        worker[i].job.professional_tital = (char *)malloc( 50 * sizeof(char));
        if(worker[i].job.professional_tital == NULL)
        {
            free_pointer(worker);
            return 1;
        } 
        printf("请输入名字");
        scanf("%49s",worker[i].name);
        printf("请输入性别");
        scanf("%9s",worker[i].sex);
        printf("请输入出生年月日");
        scanf("%d %d %d",&worker[i].date.year,&worker[i].date.month,&worker[i].date.day);
        printf("请输入学院，职称，职务");
        scanf("%49s %49s %49s",worker[i].job.college,worker[i].job.professional_tital,worker[i].job.position);
        if (worker[i].date.year > max)
        {
            max = worker[i].date.year;
            index = i;
        }
    }
    printf("%s",worker[index].name);
    free_pointer(worker);
}
void free_pointer(STUDENT worker[])
{
    for(int i = 0;i < 5;i++)
    {
        free(worker[i].name);
        worker[i].name = NULL;
        free(worker[i].sex);
        worker[i].sex = NULL;
        free(worker[i].job.college);
        worker[i].job.college = NULL;
        free(worker[i].job.position);
        worker[i].job.position = NULL;
        free(worker[i].job.professional_tital);
        worker[i].job.college = NULL;
    }
}
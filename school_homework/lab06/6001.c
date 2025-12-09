#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
    int average;
    int *score;
}
student;

void calculate(student a[],int asize,int scoresize);
void winner(student a[],int size);




int main()
{
    int student_num;
    int judger;
    scanf("%d %d",&student_num,&judger);
    student a[student_num];

    for (int i = 0; i < student_num; i++) {
        a[i].score = malloc(judger * sizeof(int));
        if (!a[i].score) {
            for (int k = 0; k < i; k++) free(a[k].score);
            return 0;
        }
    }

    for (int i = 0; i < student_num; i++) {
        for (int j = 0; j < judger; j++) {
            if (scanf("%d", &a[i].score[j]) != 1) {
                for (int k = 0; k < student_num; k++) free(a[k].score);
                return 1;
            }
        }
    }

    calculate(a,student_num,judger);
    winner(a,student_num);
}

void calculate(student a[],int asize,int scoresize)
{
    for(int i = 0;i < asize;i++)
    {
        int total = 0;
        int max = 0;
        int min = 0;
        for(int j = 0;j < scoresize;j++)
        {
            if (a[i].score[j] > max)
            {
                max = a[i].score[j];
            }
            if(a[i].score[j] < min)
            {
                min = a[i].score[j];
            }
            total += a[i].score[j];
        }
        a[i].average = (total - max - min) / scoresize;
    }
}

void winner(student a[],int size)
{
    float max = 0;
    for(int i = 0;i < size;i++)
    {
        if((float)a[i].average > max)
        {
            max = (float)a[i].average;
        }
    }
    printf("%f",max);
}
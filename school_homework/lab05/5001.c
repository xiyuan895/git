#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 50

void add();

int first[MAX] = {0};
int second[MAX] = {0};
int output[MAX] = {0};

int main()
{
    char input_1[MAX + 1];
    char input_2[MAX + 1];
    int length;
    int index;
    scanf("%s",input_1);
    length = strlen(input_1);
    for(int i = length - 1,j = 0;i >= 0;i--,j++)
    {
        first[j] = input_1[i] - '0';
    }
    scanf("%s",input_2);
    int length_2 = strlen(input_2);
    for(int i = length_2 - 1,j = 0;i >= 0;i--,j++)
    {
        second[j] = input_2[i] - '0';
    }
    add();
    for(int i = MAX - 1;i >= 0;i--)
    {
        if(output[i] != 0)
        {
            index = i;
            break;
        }
    }
    for(int i = index;i >= 0;i--)
    {
        printf("%d",output[i]);
    }
}

void add()
{
    for(int i = 0;i < MAX;i++)
    {
        output[i] = first[i] + output[i];
    }
    for(int i = 0;i < MAX;i++)
    {
        if(output[i] >= 10)
        {
            int last,rest;
            last = output[i] % 10;
            rest = output[i] / 10;
            output[i] = last;
            output[i + 1] += rest;
        }
    }
}
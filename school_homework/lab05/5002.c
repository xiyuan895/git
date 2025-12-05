#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

bool check(char *s[],int index);


#define ROW 100
#define COLUMN 30

char input[ROW][COLUMN];

int main()
{
    char *s[ROW];
    char c;
    int i = 0;
    int j = 0;
    int index = 0;
    bool is_alpha = false;
    for(int i = 0;i < ROW; i++)
    {
        s[i] = input[i];//定义行指针
    }

    while((c = getchar()) != '\n' && c != EOF)
    {
        if(isalpha(c))
        {
            if (j >= COLUMN - 1) {  // 检查单词长度是否超出限制
                printf("单词长度超出限制！\n");
                return 1;
            }
            s[i][j++] = tolower(c);
            is_alpha = true;
        }
        else if(!isalpha(c) && is_alpha)
        {
            s[i][j] = '\0';
            i++;
            index++;
            j = 0;
            is_alpha = false;
            if (i >= ROW) {  // 检查单词数量是否超出限制
                printf("单词数量超出限制！\n");
                return 1;
            }
            if(!check(s,index))
            {
                i--;
                index --;
            }
        }
    }
    if (is_alpha) {
        s[i][j] = '\0';
        index++;
    }
    printf("%d\n",index);
}
bool check(char *s[],int index)
{
    if(index == 1)
    {
        return true;
    }
    else
    {
        for(int i = 0;i < index - 1;i++)
        {
            if(strcasecmp(s[i],s[index - 1] )== 0)
            {
                return false;
            }
        }
        return true;
    }
}
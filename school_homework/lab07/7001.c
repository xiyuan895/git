#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>    // Sleep()
#else
#include <unistd.h>     // sleep()
#endif

#define MAX_RECORDS 100
#define SCORE_FILE  "score.txt"

/* 一条成绩记录 */
typedef struct
{
    char name[20];      // 姓名（不含空格）
    int  ms;                // 反应时间（毫秒）
    char date[11];      // 日期：YYYY-MM-DD 字符串（10+1）
    char time_str[9];   // 时间：HH:MM:SS 字符串（8+1）
} Record;

/* 函数声明 */
void clear_input_buffer(void);
int  load_records(Record rec[], int max_count);
void show_records(const Record rec[], int count);
int  play_game(void);
int add_record(Record rec[], int *count, int ms);
void wait_random_seconds(int min_s, int max_s);
/* 清空内存记录并清空文件 */
void clear_records(Record rec[], int *count);
int  clear_score_file(void);

int main(void)
{
    Record records[MAX_RECORDS];
    int count;
    int choice;

    // 随机数种子：用于随机等待时间
    srand((unsigned int)time(NULL));

    // 1. 启动时从 score.txt 读入历史成绩
    count = load_records(records, MAX_RECORDS);
    printf("Loaded %d records from %s.\n\n", count, SCORE_FILE);

    // 2. 菜单循环
    while (1)
    {
        printf("---------- Reaction Time Test ----------\n");
        printf("1. Start game\n");
        printf("2. Show records\n");
        printf("3. Clear all records\n");
        printf("0. Quit\n");
        printf("Please choose: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input, please try again.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();   // 吃掉行尾的回车

        if (choice == 0)
        {
            printf("Bye.\n");
            break;
        }

        if (choice == 1)
        {
            // 3. 玩一局游戏，得到反应时间 T（毫秒）
            int ms = play_game();
            if (ms < 0)
            {
                printf("Game failed, please try again.\n");
                continue;
            }

            printf("Save this record? (y/n): ");
            int ch = getchar();
            clear_input_buffer();

            if (ch == 'y' || ch == 'Y')
            {
                // 4. 追加记录到内存和文件中
                if (add_record(records, &count, ms) == 1)
                    printf("Record saved.\n");
                else
                    printf("Failed to save record.\n");
            }
        }
        else if (choice == 2)
        {
            // 5. 查看成绩列表
            show_records(records, count);
        }
        // 加入了清空数组的选项
        else if (choice == 3)
        {
            printf("Are you sure to clear all records and truncate %s? (y/n): ", SCORE_FILE);
            int ch = getchar();
            clear_input_buffer();
            if (ch == 'y' || ch == 'Y') {
                if (clear_score_file() == 0) {
                    clear_records(records, &count);
                    printf("All records cleared (memory + %s).\n", SCORE_FILE);
                } else {
                    printf("Failed to clear %s.\n", SCORE_FILE);
                }
            } else {
                printf("Clear canceled.\n");
            }
        }
        else
        {
            printf("Invalid choice, please try again.\n");
        }

        printf("\n");
    }

    return 0;
}

/* 清空输入缓冲区：保证后面的 getchar 不会读到残留的回车 */
void clear_input_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* 丢弃多余字符 */
    }
}

/* 随机等待 min_s ~ max_s 秒 */
void wait_random_seconds(int min_s, int max_s)
{
    int delay = rand() % (max_s - min_s + 1) + min_s;
#ifdef _WIN32
    Sleep(delay * 1000);
#else
    sleep(delay);
#endif
}

/* 一局游戏：随机等待 + 计时
   返回反应时间（毫秒），出错时返回 -1 */
int play_game(void)
{
    int ch;
    clock_t start, end;
    double elapsed_ms;

    printf("\n(Waiting randomly, please do NOT press anything...)\n");
    wait_random_seconds(1, 3);

    printf("Now press Enter!\n");
    fflush(stdout);   // 确保提示立刻显示

    // 开始计时
    start = clock();

    // 等待玩家按下 Enter（读到 '\n' 结束）
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        // 什么也不做，只是等待回车
    }

    end = clock();

    elapsed_ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("Your reaction time: %.0f ms.\n", elapsed_ms);

    if (elapsed_ms < 0)
    {
        return -1;
    }
    return (int)(elapsed_ms + 0.5);  // 四舍五入
}

/* =========================================================
   TODO-1: load_records
   功能：
     从成绩文件 SCORE_FILE（文本格式）中读取历史记录，
     填充到记录数组 rec 中，并返回读取条数。

   参数：
     rec       - 记录数组（输出）；
     max_count - 数组容量上限。

   返回值：
     成功读取的记录条数（0 表示没有记录或文件不存在）。

   文件格式（每行）：
     name ms YYYY-MM-DD HH:MM:SS
     例如：Alice 320 2025-11-29 14:03:59
   ========================================================= */
int load_records(Record rec[], int max_count)
{

    int count = 0;
    // TODO-1: 在此处实现从文件读取记录到 rec[] 中的逻辑
    FILE *f = fopen(SCORE_FILE,"r");
    if(!f) return 0;
    while(fscanf(f,"%19s %d %10s %8s",
        rec[count].name,
        &rec[count].ms,
        rec[count].date,
        rec[count].time_str
    ) != EOF && count < max_count)
    {
        count++;
    }
    fclose(f);
    return count;
}

/* =========================================================
   TODO-2: show_records
   功能：
     以表格形式在屏幕上输出所有成绩记录。
     每行显示：编号、姓名、反应时间（毫秒）、记录时间。

   参数：
     rec   - 记录数组；
     count - 有效记录条数。

   返回值：
     无（void）。
   ========================================================= */
void show_records(const Record rec[], int count)
{
    // TODO-2: 在此处实现遍历数组并格式化输出的逻辑
    printf("编号  姓名         反应时间(ms)   记录时间\n");
    printf("----  ------------  --------------  -------------------\n");
    for (int i = 0; i < count; i++)
    {
        printf("%-4d  %-12s  %-14d  %s %s\n",
               i + 1,
               rec[i].name,
               rec[i].ms,
               rec[i].date,
               rec[i].time_str);
    }
    if (count == 0) 
    {
        printf("(无记录)\n");
    }
}

/* =========================================================
   add_record
  功能：
     向数组末尾追加一条新记录，并写入 score.txt。

   参数：
     rec[]   - 记录数组（输入 / 输出）
     count   - 当前记录数的指针
     ms      - 本次反应时间（毫秒）

   返回值：
     1   表示成功追加1条记录
    -1   表示发生异常（数组已满、输入错误、文件写入失败）
   ========================================================= */
int add_record(Record rec[], int *count, int ms)
{
    if (!count || *count >= MAX_RECORDS) return -1;

    printf("Enter name (no spaces): ");
    fflush(stdout);
    if (scanf("%19s", rec[*count].name) != 1) {
        clear_input_buffer();
        return -1;
    }

    clear_input_buffer();
    rec[*count].ms = ms;

    /* 获取当前日期和时间字符串 */
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    if (!tm) return -1;
    if (strftime(rec[*count].date, sizeof rec[*count].date, "%Y-%m-%d", tm) == 0) return -1;
    if (strftime(rec[*count].time_str, sizeof rec[*count].time_str, "%H:%M:%S", tm) == 0) return -1;

    FILE *f = fopen(SCORE_FILE,"a");
    if (!f) return -1;
    if (fprintf(f, "%.19s %d %.10s %.8s\n",
                rec[*count].name,
                rec[*count].ms,
                rec[*count].date,
                rec[*count].time_str) < 0) 
    {
        fclose(f);
        return -1;
    }

    fclose(f);
    (*count)++;
    return 1;
}

/* =========================================================
   清空内存记录数组并重置计数
   参数：
     rec   - 记录数组（将被清零）
     count - 指向当前记录数的指针（将被置 0）
   返回：无
   ========================================================= */
void clear_records(Record rec[], int *count)
{
    if (!count) return;
    *count = 0;
    /* 可选地把数组内容清零，避免残留数据 */
    memset(rec, 0, sizeof(Record) * MAX_RECORDS);
}

/* =========================================================
   清空成绩文件 SCORE_FILE（截断为 0 字节）
   返回：0 表示成功，-1 表示失败
   ========================================================= */
int clear_score_file(void)
{
    FILE *f = fopen(SCORE_FILE, "w"); /* "w" 会截断或创建文件 */
    if (!f) return -1;
    fclose(f);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 歌曲节点结构体
typedef struct Song {
    int id;
    char title[100];
    char artist[50];
    char filepath[300];
    struct Song* prev;
    struct Song* next;
} Song;

// 播放列表管理器
typedef struct PlaylistManager{
    Song* head;
    Song* tail;
    Song* current;
    int song_count;
} PlaylistManager;

// 函数声明
void init_playlist_manager(PlaylistManager* manager);                           // 初始化链表
int load_songs_from_file(PlaylistManager* manager, const char* filename);       // 从文件中读取到链表
void add_song(PlaylistManager* manager, const char* title, const char* artist,  // 人工增加音乐
              const char* filepath);
int delete_song_by_title(PlaylistManager* manager, const char* title);                   // 删除指定名字的音乐
int play_song_by_title(PlaylistManager* manager, const char* title);                     // 根据名字播放音乐
void display_playlist(PlaylistManager* manager);                                // 显示播放列表（正向）
void display_playlist_reverse(PlaylistManager* manager);                        // 显示播放列表（反向）
int export_playlist(PlaylistManager* manager, const char* filename);            // 导出歌单
void next_song(PlaylistManager* manager);                                       // 下一首歌
void previous_song(PlaylistManager* manager);                                   // 上一首歌
int play_song_random(PlaylistManager* manager);                                 // 随机播放音乐（非必做）
void sort_by_title(PlaylistManager* manager);                                   // 按照歌曲名排序（非必做）
void destroy_playlist(PlaylistManager* manager);                                  // 清空播放列表

// linux/Mac 版本
// void play_audio(const char* filename) {
//     char command[256];
//     FILE *mp3File = fopen(filename, "rb");
//     if (!mp3File) {
//         printf("无法打开文件 %s\n", filename);
//         return;
//     }
//     else{
//         printf("Founded File!!");
//     }
//     snprintf(command, sizeof(command), "afplay \"%s\"", filename);
//     int ret = system(command);
//     if (ret != 0) {
//         printf("播放失败或中断，请检查文件格式是否支持。\n");
//     }
// }

// Windows 版本
void play_audio(const char* filename){
    char command[256];
    FILE *mp3File = fopen(filename, "rb");
    if (!mp3File) {
        printf("无法打开文件 %s\n", filename);
        return;
    }
    else{
        printf("Founded File!!");
    }
    snprintf(command, sizeof(command), "start \"\" \"%s\"", filename);
    int ret = system(command);
    if (ret != 0) {
        printf("播放失败或中断，请检查文件格式是否支持。\n");
    }
    
    // 或者使用 Windows Media Player
    // sprintf(command, "wmplayer \"%s\"", filename);
    // system(command);
}


// 初始化播放管理器
void init_playlist_manager(PlaylistManager* manager){
    manager->head = NULL;
    manager->tail = NULL;
    manager->current = NULL;
    manager->song_count = 0;
}

static char *trim(char *s) {
    if (!s) return s;
    while (*s && isspace((unsigned char)*s)) s++;
    if (*s == '\0') return s;
    char *end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }
    return s;
}
// 0. 从文件读取内容构建双向链表
int load_songs_from_file(PlaylistManager* manager, const char* filename) 
{
    
    if (!manager || !filename) return -1;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("load_songs_from_file: 无法打开文件");
        return -1;
    }

    char line[1024];
    int loaded = 0;

    while (fgets(line, sizeof(line), fp)) {
        // 去除换行
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') line[len-1] = '\0';

        // 跳过空行和注释行
        char *p = line;
        while (*p && isspace((unsigned char)*p)) p++;
        if (*p == '\0' || *p == '#') continue;

        // 格式: title,artist,filepath
        char *title = strtok(p, ",");
        char *artist = strtok(NULL, ",");
        char *filepath = strtok(NULL, ",");

        title = title ? trim(title) : NULL;
        artist = artist ? trim(artist) : NULL;
        filepath = filepath ? trim(filepath) : NULL;

        add_song(manager, title, artist, filepath);
        loaded++;
    }

    fclose(fp);
    return 0;
}

// 1. 在链表末尾添加歌曲
void add_song(PlaylistManager* manager, const char* title, const char* artist, const char* filepath) {
    Song *temp = malloc(sizeof(Song));
    if (!temp) {
        fprintf(stderr, "add_song: 内存分配失败\n");
        return;
    }

    // 初始化字段，保证以防未传入字符串时安全
    temp->id = manager->song_count + 1;
    if (title) strncpy(temp->title, title, sizeof(temp->title)-1);
    else temp->title[0] = '\0';
    temp->title[sizeof(temp->title)-1] = '\0';

    if (artist) strncpy(temp->artist, artist, sizeof(temp->artist)-1);
    else temp->artist[0] = '\0';
    temp->artist[sizeof(temp->artist)-1] = '\0';

    if (filepath) strncpy(temp->filepath, filepath, sizeof(temp->filepath)-1);
    else temp->filepath[0] = '\0';
    temp->filepath[sizeof(temp->filepath)-1] = '\0';

    temp->next = NULL;
    temp->prev = NULL;
    if(manager->song_count == 0)
    {
        manager->head = temp;
        manager->tail = temp;
        manager->current = temp;
    }
    else
    {
        temp->prev = manager->tail;
        manager->tail->next = temp;
        manager->tail = temp;
    }
    manager->song_count++;
    return;
}

// 2. 按标题删除歌曲
int delete_song_by_title(PlaylistManager* manager, const char* title) 
{
    if(manager == NULL)return 0;

    Song *temp = manager->head;
    while(temp != NULL)
    {
        if(strcmp(title,temp->title) == 0)
        {
            if(manager->song_count == 1)
            {
                manager->head = NULL;
                manager->tail = NULL;
                manager->current = NULL;
                
            }
            else if(temp == manager->head)
            {
                manager->head = temp->next;
                manager->head->prev = NULL;
                
            }
            else if (temp == manager->tail)
            {
                manager->tail = temp->prev;
                manager->tail->next = NULL;
                
            }
            else
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                
            }
            free(temp);
            if(manager->current == NULL) manager->current = manager->head;
            manager->song_count--;
            break;
        }
        else
        {
            temp = temp->next;
        }
    }
    return 0;
}

// 3. 播放歌曲
int play_song_by_title(PlaylistManager* manager, const char* title)
{
    Song *temp = manager->head;
    while(temp != NULL)
    {
        if(strcmp(title,temp->title) == 0)
        {
            manager->current = temp;
            play_audio(temp->filepath);
            break;
        }
        else
        {
            temp = temp->next;
        }
    }
    return 0;
}

// 4. 显示播放列表（正向遍历）
void display_playlist(PlaylistManager* manager) 
{
    Song *temp = manager->head;
    while(temp != NULL)
    {
        printf("%s %s %s\n",temp->title,temp->artist,temp->filepath);
        temp = temp->next;
    }
    return;
}

// 5. 显示播放列表（反向遍历）
void display_playlist_reverse(PlaylistManager* manager) 
{
    Song *temp = manager->tail;
    while(temp != NULL)
    {
        printf("%s %s %s\n",temp->title,temp->artist,temp->filepath);
        temp = temp->prev;
    }
    return;
}

// 6. 将播放列表保存到文件
int export_playlist(PlaylistManager* manager, const char* filename) 
{
    if (!manager || !filename) return -1;

    FILE *fp = fopen(filename, "a");
    if (!fp) {
        perror("export_playlist: 无法打开文件");
        return -2;
    }

    Song *temp = manager->head;
    while (temp != NULL) {
        // 格式: title|artist|filepath
        fprintf(fp, "%s|%s|%s\n", temp->title, temp->artist, temp->filepath);
        temp = temp->next;
    }

    fclose(fp);
    return 0;
    return 0;
}

// 7. 下一首
void next_song(PlaylistManager* manager) 
{
    if (!manager || !manager->current) return;
    if(manager->current->next)
    {
        manager->current = manager->current->next;
        
    }
    else manager->current = manager->head;
    play_audio(manager->current->filepath);
    return;
}

// 8. 上一首
void previous_song(PlaylistManager* manager) 
{
    if (!manager || !manager->current) return;
    if(manager->current->prev)
    {
        
        manager->current = manager->current->prev;
    }
    
    else manager->current = manager->tail;
    play_audio(manager->current->filepath);
    return;
}

// 9. 随机播放歌曲（非必做）
int play_song_random(PlaylistManager* manager) {
    return 0;
}

// 10. 按歌曲标题排序（非必做）
void sort_by_title(PlaylistManager* manager) {
    return;
}

// 11. 清空播放列表
void destroy_playlist(PlaylistManager* manager) {
    Song* current = manager->head;
    while (current != NULL) {
        Song* next = current->next;
        free(current);
        current = next;
    }
    init_playlist_manager(manager);
    printf("播放列表已清空\n");
}


void display_menu() {
    printf("\n");
    printf("链表音乐播放器管理器\n");
    printf("==========================================\n");
    printf("1. 添加歌曲\n");
    printf("2. 删除歌曲 (按标题)\n");
    printf("3. 播放歌曲 (按标题)\n");
    printf("4. 显示播放列表 (正向)\n");
    printf("5. 显示播放列表 (逆向)\n");
    printf("6. 导出歌单\n");
    printf("7. 切换到下一首歌\n");
    printf("8. 切换到上一首歌\n");
    printf("9. 随机播放歌曲(非必做)\n");
    printf("10. 按照歌曲名排序(非必做)\n");
    printf("11. 清空播放列表\n");
    printf("0. 退出程序\n");
    printf("==========================================\n");
    printf("请选择操作 (0-11): ");
}

// 清除输入缓冲区
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 获取用户输入的字符串
void get_user_input(char* buffer, int size, const char* prompt) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);

    // 去除换行符
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }
}

// 主函数 - 交互式程序
int main() {
    PlaylistManager manager;
    init_playlist_manager(&manager);
    load_songs_from_file(&manager,"song_list.txt");

    printf("=== 双向链表音乐播放器管理器 ===\n");
    printf("已加载 %d 首示例歌曲\n", manager.song_count);
    manager.current = manager.head;
    int choice;
    char input[100];

    do {
        display_menu();

        if (scanf("%d", &choice) != 1) {
            printf("无效输入，请输入数字\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: {                   // 添加歌曲
                char title[100], artist[50], filepath[300];
                float duration;

                get_user_input(title, sizeof(title), "请输入歌曲标题: ");
                get_user_input(artist, sizeof(artist), "请输入作者: ");
                get_user_input(filepath, sizeof(filepath), "请输入歌曲路径: ");
                clear_input_buffer();

                add_song(&manager, title, artist, filepath);
                break;
            }
            case 2: {                   // 删除歌曲 (按标题)
                char title[100];
                get_user_input(title, sizeof(title), "请输入要删除的歌曲标题: ");
                int res = delete_song_by_title(&manager, title);
                break;
            }
            case 3: {                   // 播放歌曲（按歌曲名）
                char title[100];
                get_user_input(title, sizeof(title), "请输入要播放的歌曲标题: ");
                int res = play_song_by_title(&manager, title);
                break;
            }
            case 4: {                   // 显示播放列表（正向）
                display_playlist(&manager);
                break;
            }
            case 5: {                   // 显示播放列表（逆向）
                display_playlist_reverse(&manager);
                break;
            }
            case 6: {                   // 导出播放列表
                char path2export[300];
                get_user_input(path2export, sizeof(path2export), "请输入要导出的目标文件名: ");
                int res = export_playlist(&manager, path2export);
                break;
            }
            case 7: {                   // 播放下一首歌曲
                next_song(&manager);
                break;
            }
            case 8: {                   // 播放上一首歌曲
                previous_song(&manager);
                break;
            }
            case 9: {                   // 随机播放歌曲(非必做)
                int res = play_song_random(&manager);
                break;
            }
            case 10: {                  // 按照歌曲名排序(非必做)
                sort_by_title(&manager);
                break;
            }
            case 11: {                  // 清空播放列表
                destroy_playlist(&manager);
                break;
            }
            case 0: // 退出程序
                printf("感谢使用链表音乐播放器管理器!\n");
                break;
            default:
                printf("? 无效选择，请重新输入\n");
                break;
        }

        // 暂停，让用户看到结果
        if (choice != 0) {
            printf("\n按回车键继续...");
            getchar();
        }

    } while (choice != 0);

    // 清理内存
    destroy_playlist(&manager);

    return 0;
}
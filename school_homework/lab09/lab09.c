#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 栈元素：存储括号类型（{/}/[/]）和所在索引（便于报错定位）
typedef struct {
    char bracket;  // 括号字符
    int position;  // 括号在JSON字符串中的位置（从0开始）
} StackElem;

// 栈结构体（动态扩容，避免固定容量限制）
typedef struct {
    StackElem* data;     // 栈数据数组
    int top;             // 栈顶指针（-1表示空栈）
    int capacity;        // 当前栈容量
    int max_capacity;    // 最大容量
} Stack;

// 栈操作结果枚举（增强健壮性）
typedef enum {
    STACK_OK,           // 操作成功
    STACK_EMPTY,        // 栈空（弹栈/取栈顶失败）
    STACK_FULL,         // 栈满（压栈失败）
    STACK_MEM_ERR       // 内存分配失败
} StackResult;

// 前置函数声明
StackResult stackInit(Stack* stack, int init_capacity, int max_capacity);
StackResult stackPush(Stack* stack, char bracket, int position);
StackResult stackPop(Stack* stack, StackElem* elem);
StackResult stackPeek(Stack* stack, StackElem* elem);
int stackIsEmpty(const Stack* stack);
void stackDestroy(Stack* stack);

// ----------------------------// 学生需实现的栈接口// ----------------------------
// 1. 初始化栈（指定初始容量和最大容量）
StackResult stackInit(Stack* stack, int init_capacity, int max_capacity){
    if (stack == NULL) return STACK_MEM_ERR;
    if (init_capacity <= 0 || max_capacity <= 0 || init_capacity > max_capacity) return STACK_MEM_ERR;
    stack->data = (StackElem*)malloc(init_capacity * sizeof(StackElem));
    if (stack->data == NULL) return STACK_MEM_ERR;
    stack->top = -1;
    stack->capacity = init_capacity;
    stack->max_capacity = max_capacity;
    return STACK_OK;
}

// 2. 压栈（将数据存入栈）
StackResult stackPush(Stack* stack, char bracket, int position){
    if (stack == NULL) return STACK_MEM_ERR;
    if (stack->top + 1 >= stack->capacity) {
        if (stack->capacity == stack->max_capacity) return STACK_FULL;
        int new_capacity = stack->capacity * 2;
        if (new_capacity > stack->max_capacity) new_capacity = stack->max_capacity;
        StackElem *tmp = (StackElem*)realloc(stack->data, new_capacity * sizeof(StackElem));
        if (tmp == NULL) return STACK_MEM_ERR;
        stack->data = tmp;
        stack->capacity = new_capacity;
    }
    stack->top++;
    stack->data[stack->top].bracket = bracket;
    stack->data[stack->top].position = position;
    return STACK_OK;
}

// 3. 弹栈（取出栈顶元素，通过elem输出）
StackResult stackPop(Stack* stack, StackElem* elem){
    // 学生实现：
    // 步骤1：检查栈是否空（stackIsEmpty），空则返回STACK_EMPTY
    // 步骤2：将栈顶元素赋值给elem（bracket和position）
    // 步骤3：栈顶指针-1
    // 步骤4：返回STACK_OK
    if (stackIsEmpty(stack)) return STACK_EMPTY;
    if (elem != NULL) *elem = stack->data[stack->top];
    stack->top--;
    return STACK_OK;
}
// 4. 查看栈顶
StackResult stackPeek(Stack* stack, StackElem* elem) {
    // 学生实现：
    // 步骤1：检查栈是否空（stackIsEmpty），空则返回STACK_EMPTY
    // 步骤2：将栈顶元素赋值给elem（bracket和position）
    // 步骤3：栈顶指针-1
    // 步骤4：返回STACK_OK
    if (stackIsEmpty(stack)) return STACK_EMPTY;
    if (elem != NULL) *elem = stack->data[stack->top];
    return STACK_OK;
}

// 5. 判空（返回1表示空，0表示非空）
int stackIsEmpty(const Stack* stack){
    if (stack == NULL) return 1;
    return (stack->top == -1) ? 1 : 0;
}

// 6. 销毁栈（释放内存）
void stackDestroy(Stack* stack) {
    // 学生实现：释放stack->data的内存，重置top=-1、capacity=0
    if (stack == NULL) return;
    if (stack->data != NULL) 
    {
        free(stack->data);
        stack->data = NULL;
    }
    stack->top = -1;
    stack->capacity = 0;
    stack->max_capacity = 0;
}


// 辅助函数
// 判断是否为左括号
int isLeftBracket(char ch) {
    return ch == '{' || ch == '[';
}
// 判断是否为右括号
int isRightBracket(char ch) {
    return ch == '}' || ch == ']';
}
// 判断括号是否匹配
int isBracketMatch(char left, char right) {
    return (left == '{' && right == '}') || (left == '[' && right == ']');
}


// 栈基础版本实现
int jsonBracketCheckBasic(const char *json_str) {
    // 学生实现：
    // 步骤1：处理边界情况（json_str为NULL或空字符串，返回1）
    // 步骤2：初始化栈（调用stackInit）
    // 步骤3：遍历json_str的每个字符：
    //        - 遇到左括号（{/[）：压栈（stackPush）
    //        - 遇到右括号（}/]）：弹栈并检查匹配（isBracketMatch），不匹配则返回0
    //        - 其他字符（如字母、数字、引号）：跳过
    // 步骤4：遍历结束后，若栈为空则返回1（合法），否则返回0（左括号多余）
    // 步骤5：销毁栈（stackDestroy）
    if (json_str == NULL || *json_str == '\0') return 1;
    Stack stack;
    if (stackInit(&stack, 16, 1024) != STACK_OK) return 0;
    int i = 0;
    for (; json_str[i] != '\0'; i++) {
        char ch = json_str[i];
        if (isLeftBracket(ch)) {
            if (stackPush(&stack, ch, i) != STACK_OK) {
                stackDestroy(&stack);
                return 0;
            }
        } 
        else if (isRightBracket(ch))
        {
            if (stackIsEmpty(&stack))
            {
                stackDestroy(&stack);
                return 0;
            }
            StackElem top;
            stackPop(&stack, &top);
            if (!isBracketMatch(top.bracket, ch))
            {
                stackDestroy(&stack);
                return 0;
            }
        }
    }
    int ok = stackIsEmpty(&stack) ? 1 : 0;
    stackDestroy(&stack);
    return ok;
}

// 栈进阶版本实现
// 学生任务：学习状态管理，理解字符串内的括号不应该参与匹配，同时处理转义字符
int jsonBracketCheckAdvanced(const char *json_str) {
// 学生实现：
// 步骤1：处理边界情况（json_str为NULL或空字符串，返回1）
// 步骤2：初始化栈（调用stackInit）
// 步骤3：初始化状态标记（in_string标记字符串状态，escape标记转义状态）
// 步骤4：遍历json_str的每个字符：
//        - 如果在字符串内（in_string为1）：
//             * 如果在转义状态（escape为1）：取消转义状态，继续
//             * 如果遇到转义字符'\'：进入转义状态
//             * 如果遇到引号'"'且不在转义状态：退出字符串状态
//             * 字符串内的所有括号都不处理
//        - 如果不在字符串内（in_string为0）：
//             * 如果遇到引号'"'：进入字符串状态
//             * 遇到左括号（{/[）：压栈（stackPush）
//             * 遇到右括号（}/]）：弹栈并检查匹配（isBracketMatch），不匹配则返回0
//             * 其他字符（如字母、数字、冒号等）：跳过
// 步骤5：遍历结束后，检查栈是否为空且不在字符串内，两者都满足则返回1，否则返回0
// 步骤6：销毁栈（stackDestroy）
    if (json_str == NULL || *json_str == '\0') return 1;
    Stack stack;
    if (stackInit(&stack, 16, 1024) != STACK_OK) return 0;
    int i = 0;
    bool in_string = false;
    bool escape = false;
    for (; json_str[i] != '\0'; i++) {
        char ch = json_str[i];
        if (escape)
        {
            // current char is escaped, skip special meaning
            escape = false;
            continue;
        }
        if (ch == '\\' && in_string) 
        {
            escape = true;
            continue;
        }
        if (ch == '"') {
            in_string = !in_string;
            continue;
        }
        if (in_string) {
            continue; // ignore brackets inside strings
        }
        if (isLeftBracket(ch)) {
            if (stackPush(&stack, ch, i) != STACK_OK) {
                stackDestroy(&stack);
                return 0;
            }
        } 
        else if (isRightBracket(ch)) 
        {
            if (stackIsEmpty(&stack)) {
                stackDestroy(&stack);
                return 0;
            }
            StackElem top;
            stackPop(&stack, &top);
            if (!isBracketMatch(top.bracket, ch)) 
            {
                stackDestroy(&stack);
                return 0;
            }
        }
    }
    int ok = (stackIsEmpty(&stack) && !in_string) ? 1 : 0;
    stackDestroy(&stack);
    return ok;
}

int main(){
    char str[100];
    // 输入JSON字符串
    scanf("%s", str); 
    // 栈基础版
    int result1 = jsonBracketCheckBasic(str);
    // 栈进阶版
    int result2 = jsonBracketCheckAdvanced(str);
    // 返回JSON括号匹配结果，基础版只能处理简单情况，进阶版总能返回正确答案
    printf("%d %d", result1,result2);
}
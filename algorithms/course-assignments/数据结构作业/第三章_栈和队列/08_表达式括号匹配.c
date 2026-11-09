#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_SIZE 100 /* 代码补全模板给定的最大长度。 */

typedef struct
{
    char data[MAX_SIZE];
    int top; /* 栈顶下标；空栈为 -1。 */
} SqStack;

void InitStack(SqStack* stack)
{
    stack->top = -1;
}

int StackEmpty(const SqStack* stack)
{
    return stack->top == -1;
}

int Push(SqStack* stack, char value)
{
    if (stack->top + 1 >= MAX_SIZE)
    {
        return 0;
    }
    ++stack->top;
    stack->data[stack->top] = value;
    return 1;
}

int Pop(SqStack* stack, char* value)
{
    if (StackEmpty(stack))
    {
        return 0;
    }
    *value = stack->data[stack->top];
    --stack->top;
    return 1;
}

/* 判断左右括号是否配对。 */
int IsPair(char left, char right)
{
    return (left == '(' && right == ')')
        || (left == '[' && right == ']')
        || (left == '{' && right == '}');
}

/* 扫描表达式：左括号入栈，右括号与栈顶配对。 */
int IsMatching(const char* expression)
{
    SqStack stack;
    InitStack(&stack);

    for (int i = 0; expression[i] != '\0'; ++i)
    {
        char current = expression[i];
        if (current == '(' || current == '[' || current == '{')
        {
            if (!Push(&stack, current))
            {
                return 0;
            }
        }
        else if (current == ')' || current == ']' || current == '}')
        {
            char left;
            if (!Pop(&stack, &left))
            {
                return 0;
            }
            if (!IsPair(left, current))
            {
                return 0;
            }
        }
    }

    return StackEmpty(&stack);
}

int main(void)
{
    char expression[MAX_SIZE];
    if (fgets(expression, MAX_SIZE, stdin) == NULL)
    {
        return 0;
    }

    puts(IsMatching(expression) ? "OK" : "ERROR");
    return 0;
}

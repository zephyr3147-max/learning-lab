#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_SIZE 30 /* 题面规定栈最多容纳 30 个元素。 */

typedef struct
{
    int data[MAX_SIZE];
    int top; /* 栈顶下标；空栈为 -1。 */
} SqStack;

void InitStack(SqStack* stack)
{
    stack->top = -1;
}

/* 入栈；栈满时忽略本次操作。 */
void Push(SqStack* stack, int value)
{
    if (stack->top + 1 >= MAX_SIZE)
    {
        return;
    }
    ++stack->top;
    stack->data[stack->top] = value;
}

/* 出栈；空栈时忽略本次操作。 */
void Pop(SqStack* stack)
{
    if (stack->top == -1)
    {
        return;
    }
    --stack->top;
}

int main(void)
{
    SqStack stack;
    InitStack(&stack);

    int value;
    while (scanf("%d", &value) == 1 && value != -2)
    {
        if (value == -1)
        {
            Pop(&stack);
        }
        else
        {
            Push(&stack, value);
        }
    }

    if (stack.top == -1)
    {
        puts("0");
        return 0;
    }

    /* 从栈顶下标 top 向 0 输出，就是栈顶到栈底的顺序。 */
    for (int i = stack.top; i >= 0; --i)
    {
        printf("%d", stack.data[i]);
        if (i > 0)
        {
            putchar(' ');
        }
    }
    putchar('\n');
    return 0;
}

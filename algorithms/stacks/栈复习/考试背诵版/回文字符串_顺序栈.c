#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_SIZE 10000

typedef struct
{
    char data[MAX_SIZE];
    int top;
} SqStack;

/* 初始化：top 为 -1 表示空栈。 */
void InitStack(SqStack* S)
{
    S->top = -1;
}

/* 入栈：成功返回 1，栈满返回 0。 */
int Push(SqStack* S, char ch)
{
    if (S->top == MAX_SIZE - 1)
    {
        return 0;
    }

    S->data[++S->top] = ch;
    return 1;
}

/* 出栈：成功返回 1，栈空返回 0；通过 ch 带回字符。 */
int Pop(SqStack* S, char* ch)
{
    if (S->top == -1)
    {
        return 0;
    }

    *ch = S->data[S->top--];
    return 1;
}

int IsPalindrome(const char* str)
{
    SqStack S;
    InitStack(&S);

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!Push(&S, str[i]))
        {
            return 0;
        }
    }

    for (int i = 0; str[i] != '\0'; i++)
    {
        char ch;

        if (!Pop(&S, &ch))
        {
            return 0;
        }

        if (str[i] != ch)
        {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    char str[MAX_SIZE];

    /* 最多读取 9999 个字符，为 '\0' 保留一个位置。 */
    if (scanf("%9999s", str) != 1)
    {
        return 0;
    }

    printf("%d\n", IsPalindrome(str));
    return 0;
}

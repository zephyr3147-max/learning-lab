#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int stack[30]; /* The problem sets the maximum stack size to 30. */
    int top = 0;
    int value;
    while (scanf("%d", &value) == 1 && value != -2)
    {
        if (value == -1)
        {
            if (top > 0)
            {
                --top;
            }
        }
        else if (top < 30)
        {
            stack[top++] = value;
        }
    }
    if (top == 0)
    {
        puts("0");
        return 0;
    }
    for (int i = top - 1; i >= 0; --i)
    {
        printf("%s%d", i == top - 1 ? "" : " ", stack[i]);
    }
    putchar('\n');
    return 0;
}

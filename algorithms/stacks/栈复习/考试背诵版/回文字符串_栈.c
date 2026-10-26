#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    char str[10000];
    char stack[10000];
    int top = -1;

    /* 最多读取 9999 个字符，保留一个位置存放 '\0'。 */
    if (scanf("%9999s", str) != 1)
    {
        return 0;
    }

    /* 将字符串中的字符依次入栈。 */
    for (int i = 0; str[i] != '\0'; i++)
    {
        stack[++top] = str[i];
    }

    /* 出栈顺序是原字符串的逆序，逐个比较。 */
    for (int i = 0; str[i] != '\0'; i++)
    {
        char ch = stack[top--];

        if (str[i] != ch)
        {
            printf("0\n");
            return 0;
        }
    }

    printf("1\n");
    return 0;
}

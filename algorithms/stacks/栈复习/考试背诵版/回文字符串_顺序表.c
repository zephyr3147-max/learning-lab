#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_SIZE 10000

typedef struct
{
    char data[MAX_SIZE];
    int length;
} SqList;

int IsPalindrome(const SqList* L)
{
    int left = 0;
    int right = L->length - 1;

    while (left < right)
    {
        if (L->data[left] != L->data[right])
        {
            return 0;
        }

        left++;
        right--;
    }

    return 1;
}

int main(void)
{
    SqList L;
    L.length = 0;

    /* 为字符串结束标志 '\0' 保留一个位置。 */
    if (scanf("%9999s", L.data) != 1)
    {
        return 0;
    }

    while (L.data[L.length] != '\0')
    {
        L.length++;
    }

    printf("%d\n", IsPalindrome(&L));
    return 0;
}

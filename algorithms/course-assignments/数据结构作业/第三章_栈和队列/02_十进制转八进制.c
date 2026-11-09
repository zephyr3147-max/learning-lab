#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct DigitNode
{
    int value;
    struct DigitNode* next;
} DigitNode;

/* 压入一个八进制位。 */
void Push(DigitNode** top, int value)
{
    DigitNode* node = (DigitNode*)malloc(sizeof(DigitNode));
    if (node == NULL)
    {
        exit(1);
    }
    node->value = value;
    node->next = *top;
    *top = node;
}

int main(void)
{
    long long number;
    if (scanf("%lld", &number) != 1)
    {
        return 0;
    }

    int negative = number < 0;
    if (negative)
    {
        number = -number; /* 考试数据不含 LLONG_MIN，直接取负即可。 */
    }

    DigitNode* top = NULL;
    do
    {
        Push(&top, (int)(number % 8)); /* 先得到最低位，最后才输出。 */
        number /= 8;
    } while (number != 0);

    if (negative)
    {
        putchar('-');
    }
    while (top != NULL)
    {
        DigitNode* node = top;
        top = node->next;
        printf("%d", node->value);
        free(node);
    }
    putchar('\n');
    return 0;
}

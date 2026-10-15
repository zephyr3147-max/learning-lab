#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Digit
{
    int value;
    struct Digit *next;
} Digit;

static void Push(Digit **top, int value)
{
    Digit *node = malloc(sizeof(*node));
    if (node == NULL)
    {
        exit(EXIT_FAILURE);
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
    unsigned long long magnitude = negative
        ? (unsigned long long)(-(number + 1)) + 1ULL
        : (unsigned long long)number;
    Digit *top = NULL;
    do
    {
        Push(&top, (int)(magnitude % 8ULL));
        magnitude /= 8ULL;
    } while (magnitude != 0ULL);
    if (negative)
    {
        putchar('-');
    }
    while (top != NULL)
    {
        Digit *node = top;
        printf("%d", node->value);
        top = node->next;
        free(node);
    }
    putchar('\n');
    return 0;
}

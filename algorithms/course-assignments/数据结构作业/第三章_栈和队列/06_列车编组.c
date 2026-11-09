#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node* next;
} Node;

int main(void)
{
    Node* oddFront = NULL; /* 奇数队列的队头。 */
    Node* oddRear = NULL;  /* 奇数队列的队尾。 */
    Node* evenTop = NULL;  /* 偶数栈的栈顶。 */
    int value;

    while (scanf("%d", &value) == 1)
    {
        Node* node = (Node*)malloc(sizeof(Node));
        if (node == NULL)
        {
            exit(1);
        }
        node->value = value;
        node->next = NULL;

        if (value % 2 != 0)
        {
            if (oddRear == NULL)
            {
                oddFront = node;
                oddRear = node;
            }
            else
            {
                oddRear->next = node; /* 尾插保持奇数原来的顺序。 */
                oddRear = node;
            }
        }
        else
        {
            node->next = evenTop; /* 头插让偶数逆序。 */
            evenTop = node;
        }
    }

    int first = 1;
    while (oddFront != NULL)
    {
        Node* node = oddFront;
        oddFront = node->next;
        if (first == 0)
        {
            putchar(' ');
        }
        printf("%d", node->value);
        first = 0;
        free(node);
    }
    while (evenTop != NULL)
    {
        Node* node = evenTop;
        evenTop = node->next;
        if (first == 0)
        {
            putchar(' ');
        }
        printf("%d", node->value);
        first = 0;
        free(node);
    }
    putchar('\n');
    return 0;
}

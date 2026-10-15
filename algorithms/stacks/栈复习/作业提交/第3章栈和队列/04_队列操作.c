#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

static void Enqueue(Node **front, Node **rear, int value)
{
    Node *node = malloc(sizeof(*node));
    if (node == NULL)
    {
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->next = NULL;
    if (*rear == NULL)
    {
        *front = *rear = node;
    }
    else
    {
        (*rear)->next = node;
        *rear = node;
    }
}

static int Dequeue(Node **front, Node **rear)
{
    Node *node = *front;
    int value = node->value;
    *front = node->next;
    if (*front == NULL)
    {
        *rear = NULL;
    }
    free(node);
    return value;
}

int main(void)
{
    int count;
    if (scanf("%d", &count) != 1 || count <= 0)
    {
        return 0;
    }
    Node *front = NULL;
    Node *rear = NULL;
    int value;
    for (int i = 0; i < count; ++i)
    {
        if (scanf("%d", &value) != 1)
        {
            break;
        }
        if (front == NULL)
        {
            Enqueue(&front, &rear, value);
        }
        else
        {
            long long ends = (long long)front->value + rear->value;
            if (2LL * value < ends)
            {
                Enqueue(&front, &rear, value);
                (void)Dequeue(&front, &rear);
            }
            else
            {
                Enqueue(&front, &rear, value);
            }
        }
    }
    int first = 1;
    while (front != NULL)
    {
        printf("%s%d", first ? "" : " ", Dequeue(&front, &rear));
        first = 0;
    }
    putchar('\n');
    return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node* next;
} Node;

typedef struct
{
    Node* front;
    Node* rear;
} Queue;

/* 入队：新结点接在队尾。 */
void Enqueue(Queue* queue, int value)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL)
    {
        exit(1);
    }
    node->value = value;
    node->next = NULL;
    if (queue->rear == NULL)
    {
        queue->front = node;
        queue->rear = node;
    }
    else
    {
        queue->rear->next = node;
        queue->rear = node;
    }
}

/* 出队：调用前保证队列非空。 */
int Dequeue(Queue* queue)
{
    Node* node = queue->front;
    int value = node->value;
    queue->front = node->next;
    if (queue->front == NULL)
    {
        queue->rear = NULL;
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

    Queue queue = {NULL, NULL};
    for (int i = 0; i < count; ++i)
    {
        int value;
        if (scanf("%d", &value) != 1)
        {
            break;
        }
        if (queue.front == NULL)
        {
            Enqueue(&queue, value);
            continue;
        }

        long long endpoints = (long long)queue.front->value + queue.rear->value;
        Enqueue(&queue, value);
        if (2LL * value < endpoints)
        {
            Dequeue(&queue); /* 新元素留在队尾，移除原队头。 */
        }
    }

    int first = 1;
    while (queue.front != NULL)
    {
        int value = Dequeue(&queue);
        if (first == 0)
        {
            putchar(' ');
        }
        printf("%d", value);
        first = 0;
    }
    putchar('\n');
    return 0;
}

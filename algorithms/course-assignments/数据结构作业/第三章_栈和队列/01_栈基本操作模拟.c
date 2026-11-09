#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 30 /* 题面规定栈最多容纳 30 个元素。 */

typedef struct StackNode
{
    int value;
    struct StackNode* next;
} StackNode;

/* 入栈；栈满时忽略本次操作。 */
void Push(StackNode** top, int* size, int value)
{
    if (*size >= MAX_SIZE)
    {
        return;
    }
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    if (node == NULL)
    {
        exit(1);
    }
    node->value = value;
    node->next = *top;
    *top = node;
    ++*size;
}

/* 出栈；空栈时忽略本次操作。 */
void Pop(StackNode** top, int* size)
{
    if (*size == 0)
    {
        return;
    }
    StackNode* node = *top;
    *top = node->next;
    --*size;
    free(node);
}

int main(void)
{
    StackNode* top = NULL;
    int size = 0;
    int value;

    while (scanf("%d", &value) == 1 && value != -2)
    {
        if (value == -1)
        {
            Pop(&top, &size);
        }
        else
        {
            Push(&top, &size, value);
        }
    }

    if (size == 0)
    {
        puts("0");
        return 0;
    }

    int first = 1;
    while (top != NULL)
    {
        StackNode* node = top;
        printf("%s%d", first ? "" : " ", node->value);
        first = 0;
        top = node->next;
        free(node);
    }
    putchar('\n');
    return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int count;
    if (scanf("%d", &count) != 1 || count <= 0)
    {
        return 0;
    }

    /* 题面要求顺序存储，容量取输入个数，每次操作只增加一个元素。 */
    int* deque = (int*)malloc((size_t)count * sizeof(int));
    if (deque == NULL)
    {
        exit(1);
    }

    int front = 0; /* 队头在数组中的下标。 */
    int size = 0;  /* 当前元素个数。 */
    for (int i = 0; i < count; ++i)
    {
        int value;
        if (scanf("%d", &value) != 1)
        {
            break;
        }
        if (size == 0)
        {
            deque[front] = value;
            size = 1;
            continue;
        }

        int rear = (front + size - 1) % count;
        long long endpoints = (long long)deque[front] + deque[rear];
        if (2LL * value < endpoints)
        {
            front = (front + count - 1) % count; /* 从队头前插入。 */
            deque[front] = value;
        }
        else
        {
            deque[(front + size) % count] = value; /* 从队尾插入。 */
        }
        ++size;
    }

    for (int i = 0; i < size; ++i)
    {
        if (i > 0)
        {
            putchar(' ');
        }
        printf("%d", deque[(front + i) % count]);
    }
    putchar('\n');
    free(deque);
    return 0;
}

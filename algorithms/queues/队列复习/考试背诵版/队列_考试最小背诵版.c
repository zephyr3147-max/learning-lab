#include <stdio.h>
#define MAXSIZE 100
typedef int ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int front;
    int rear;
} SqQueue;

/* 初始化：front 指向队头，rear 指向下一次入队位置。O(1)。 */
void InitQueue(SqQueue *Q)
{
    Q->front = 0;
    Q->rear = 0;
}

/* 判空：队头与下一次入队位置重合。O(1)。 */
int QueueEmpty(const SqQueue *Q)
{
    return Q->front == Q->rear;
}

/* 判满：牺牲一个单元，避免与判空条件冲突。O(1)。 */
int QueueFull(const SqQueue *Q)
{
    return (Q->rear + 1) % MAXSIZE == Q->front;
}

/* 求长：循环距离；最多保存 MAXSIZE-1 个元素。O(1)。 */
int QueueLength(const SqQueue *Q)
{
    return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}

/* 入队：在 rear 处写入，再让 rear 循环后移。O(1)。 */
int EnQueue(SqQueue *Q, ElemType e)
{
    if (QueueFull(Q))
    {
        return 0;
    }
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return 1;
}

/* 出队：读取 front 处数据，再让 front 循环后移。O(1)。 */
int DeQueue(SqQueue *Q, ElemType *e)
{
    if (QueueEmpty(Q))
    {
        return 0;
    }
    if (e != NULL)
    {
        *e = Q->data[Q->front];
    }
    Q->front = (Q->front + 1) % MAXSIZE;
    return 1;
}

/* 取队头：只读，不删除；失败不改输出。O(1)。 */
int GetHead(const SqQueue *Q, ElemType *e)
{
    if (QueueEmpty(Q) || e == NULL)
    {
        return 0;
    }
    *e = Q->data[Q->front];
    return 1;
}

/* 清空：固定数组不用 free，恢复初始下标。O(1)。 */
void ClearQueue(SqQueue *Q)
{
    Q->front = 0;
    Q->rear = 0;
}

/* 自动演示：顺序入队 10、20、30，按 10、20、30 出队。 */
int main(void)
{
    SqQueue Q;
    InitQueue(&Q);
    if (!EnQueue(&Q, 10) || !EnQueue(&Q, 20) || !EnQueue(&Q, 30))
    {
        return 1;
    }
    ElemType e;
    if (GetHead(&Q, &e))
    {
        printf("head: %d\n", e);
    }
    while (DeQueue(&Q, &e))
    {
        printf("%d", e);
        if (!QueueEmpty(&Q))
        {
            printf(" ");
        }
    }
    printf("\n");
    ClearQueue(&Q);
    return 0;
}


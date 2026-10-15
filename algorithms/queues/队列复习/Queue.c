#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef QUEUE_TEST_ALLOCATOR
void *QueueTestMalloc(size_t bytes);
void QueueTestFree(void *p);
#define QMALLOC QueueTestMalloc
#define QFREE QueueTestFree
#else
#define QMALLOC malloc
#define QFREE free
#endif

/* 计算逻辑 offset 对应的物理下标，避免 front+offset 溢出。
 * 前提：capacity>0，front<capacity，offset<capacity。
 */
static size_t Index(const Queue *Q, size_t offset)
{
    size_t remaining = Q->capacity - Q->front;
    if (offset < remaining)
    {
        return Q->front + offset;
    }
    return offset - remaining;
}

int QueueInit(Queue *Q, size_t capacity)
{
    if (Q == NULL || Q->data != NULL || Q->size != 0 || Q->front != 0
        || Q->capacity != 0 || capacity == 0 || capacity > SIZE_MAX / sizeof(ElemType))
    {
        return QUEUE_ERR;
    }
    ElemType *p = QMALLOC(capacity * sizeof(*p));
    if (p == NULL)
    {
        return QUEUE_ERR;
    }
    Q->data = p;
    Q->capacity = capacity;
    return QUEUE_OK;
}

int QueueEmpty(const Queue *Q)
{
    return Q != NULL && Q->size == 0;
}

size_t QueueLength(const Queue *Q)
{
    return Q != NULL ? Q->size : 0;
}

int QueuePeek(const Queue *Q, ElemType *e)
{
    if (Q == NULL || Q->size == 0 || e == NULL)
    {
        return QUEUE_ERR;
    }
    *e = Q->data[Q->front];
    return QUEUE_OK;
}

int QueueReserve(Queue *Q, size_t capacity)
{
    if (Q == NULL || Q->data == NULL || capacity > SIZE_MAX / sizeof(ElemType))
    {
        return QUEUE_ERR;
    }
    if (capacity <= Q->capacity)
    {
        return QUEUE_OK;
    }
    ElemType *p = QMALLOC(capacity * sizeof(*p));
    if (p == NULL)
    {
        return QUEUE_ERR;
    }
    for (size_t i = 0; i < Q->size; ++i)
    {
        p[i] = Q->data[Index(Q, i)];
    }
    QFREE(Q->data);
    Q->data = p;
    Q->capacity = capacity;
    Q->front = 0;
    return QUEUE_OK;
}

static int EnsureCapacity(Queue *Q, size_t needed)
{
    size_t limit = SIZE_MAX / sizeof(ElemType);
    size_t capacity = Q->capacity;
    while (capacity < needed)
    {
        if (capacity > limit / 2)
        {
            capacity = needed;
            break;
        }
        capacity *= 2;
    }
    return QueueReserve(Q, capacity);
}

int QueueEnqueueMany(Queue *Q, const ElemType a[], size_t n)
{
    if (Q == NULL || Q->data == NULL || (n > 0 && a == NULL)
        || n > SIZE_MAX / sizeof(ElemType) - Q->size)
    {
        return QUEUE_ERR;
    }
    if (n == 0)
    {
        return QUEUE_OK;
    }
    if (!EnsureCapacity(Q, Q->size + n))
    {
        return QUEUE_ERR;
    }
    for (size_t i = 0; i < n; ++i)
    {
        Q->data[Index(Q, Q->size)] = a[i];
        ++Q->size;
    }
    return QUEUE_OK;
}

int QueueEnqueue(Queue *Q, ElemType e)
{
    return QueueEnqueueMany(Q, &e, 1);
}

int QueueDequeue(Queue *Q, ElemType *e)
{
    if (Q == NULL || Q->size == 0)
    {
        return QUEUE_ERR;
    }
    if (e != NULL)
    {
        *e = Q->data[Q->front];
    }
    if (Q->front == Q->capacity - 1)
    {
        Q->front = 0;
    }
    else
    {
        ++Q->front;
    }
    --Q->size;
    if (Q->size == 0)
    {
        Q->front = 0;
    }
    return QUEUE_OK;
}

void QueueClear(Queue *Q)
{
    if (Q != NULL)
    {
        Q->front = 0;
        Q->size = 0;
    }
}

void QueueDestroy(Queue *Q)
{
    if (Q != NULL)
    {
        QFREE(Q->data);
        Q->data = NULL;
        Q->front = 0;
        Q->size = 0;
        Q->capacity = 0;
    }
}

void QueuePrint(const Queue *Q)
{
    if (Q == NULL)
    {
        return;
    }
    for (size_t i = 0; i < Q->size; ++i)
    {
        if (i != 0)
        {
            printf(" ");
        }
        printf("%d", Q->data[Index(Q, i)]);
    }
    printf("\n");
}

/* 链队列：尾插头删，rear 保证尾插为 O(1)。 */
int LinkQueueInit(LinkQueue *Q)
{
    if (Q == NULL || Q->front != NULL || Q->rear != NULL || Q->size != 0)
    {
        return QUEUE_ERR;
    }
    return QUEUE_OK;
}

int LinkQueueEmpty(const LinkQueue *Q)
{
    return Q != NULL && Q->front == NULL;
}

size_t LinkQueueLength(const LinkQueue *Q)
{
    return Q != NULL ? Q->size : 0;
}

int LinkQueuePeek(const LinkQueue *Q, ElemType *e)
{
    if (Q == NULL || Q->front == NULL || e == NULL)
    {
        return QUEUE_ERR;
    }
    *e = Q->front->data;
    return QUEUE_OK;
}

int LinkQueueEnqueue(LinkQueue *Q, ElemType e)
{
    if (Q == NULL || Q->size == SIZE_MAX)
    {
        return QUEUE_ERR;
    }
    QueueNode *p = QMALLOC(sizeof(*p));
    if (p == NULL)
    {
        return QUEUE_ERR;
    }
    p->data = e;
    p->next = NULL;
    if (Q->rear == NULL)
    {
        Q->front = p;
    }
    else
    {
        Q->rear->next = p;
    }
    Q->rear = p;
    ++Q->size;
    return QUEUE_OK;
}

int LinkQueueDequeue(LinkQueue *Q, ElemType *e)
{
    if (Q == NULL || Q->front == NULL)
    {
        return QUEUE_ERR;
    }
    QueueNode *p = Q->front;
    if (e != NULL)
    {
        *e = p->data;
    }
    Q->front = p->next;
    if (Q->front == NULL)
    {
        Q->rear = NULL;
    }
    QFREE(p);
    --Q->size;
    return QUEUE_OK;
}

void LinkQueueClear(LinkQueue *Q)
{
    if (Q != NULL)
    {
        while (LinkQueueDequeue(Q, NULL))
        {
            /* Dequeue 内部负责释放并维护首尾。 */
        }
    }
}

void LinkQueueDestroy(LinkQueue *Q)
{
    LinkQueueClear(Q);
}

void LinkQueuePrint(const LinkQueue *Q)
{
    if (Q == NULL)
    {
        return;
    }
    for (const QueueNode *p = Q->front; p != NULL; p = p->next)
    {
        if (p != Q->front)
        {
            printf(" ");
        }
        printf("%d", p->data);
    }
    printf("\n");
}


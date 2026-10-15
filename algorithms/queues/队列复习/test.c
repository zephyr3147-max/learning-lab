#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void Check(int condition, const char *text, int line)
{
    if (!condition)
    {
        fprintf(stderr, "Check failed at line %d: %s\n", line, text);
        exit(1);
    }
}
#define REQUIRE(x) Check((x), #x, __LINE__)

#ifdef QUEUE_TEST_ALLOCATOR
static int failNext = 0;
static int liveBlocks = 0;
void *QueueTestMalloc(size_t bytes)
{
    if (failNext)
    {
        failNext = 0;
        return NULL;
    }
    void *p = malloc(bytes);
    if (p != NULL)
    {
        ++liveBlocks;
    }
    return p;
}
void QueueTestFree(void *p)
{
    if (p != NULL)
    {
        REQUIRE(liveBlocks > 0);
        --liveBlocks;
    }
    free(p);
}
#endif

static void Compare(const Queue *Q, const LinkQueue *L, const int a[], size_t n)
{
    REQUIRE(QueueLength(Q) == n && LinkQueueLength(L) == n);
    REQUIRE(QueueEmpty(Q) == (n == 0) && LinkQueueEmpty(L) == (n == 0));
    REQUIRE(Q->size <= Q->capacity && Q->front < Q->capacity);
    const QueueNode *p = L->front;
    const QueueNode *last = NULL;
    for (size_t i = 0; i < n; ++i)
    {
        REQUIRE(Q->data[(Q->front + i) % Q->capacity] == a[i]);
        REQUIRE(p != NULL && p->data == a[i]);
        last = p;
        p = p->next;
    }
    REQUIRE(p == NULL && last == L->rear);
    int e = -999;
    if (n > 0)
    {
        REQUIRE(QueuePeek(Q, &e) && e == a[0]);
        REQUIRE(LinkQueuePeek(L, &e) && e == a[0]);
        REQUIRE(L->rear->next == NULL);
    }
    else
    {
        REQUIRE(L->front == NULL && L->rear == NULL);
        REQUIRE(!QueuePeek(Q, &e) && e == -999);
        REQUIRE(!LinkQueuePeek(L, &e) && e == -999);
    }
}

int main(void)
{
    Queue Q = {0};
    LinkQueue L = {0};
    int e = -999;
    REQUIRE(!QueueInit(NULL, 2) && !QueueInit(&Q, 0));
    REQUIRE(!QueueInit(&Q, SIZE_MAX));
    REQUIRE(!QueueEnqueue(&Q, 1) && !QueueReserve(&Q, 1));
#ifdef QUEUE_TEST_ALLOCATOR
    failNext = 1;
    REQUIRE(!QueueInit(&Q, 4) && Q.data == NULL);
#endif
    REQUIRE(QueueInit(&Q, 4) && LinkQueueInit(&L));
    REQUIRE(!QueueInit(&Q, 2) && !LinkQueueInit(NULL));
    REQUIRE(!QueueDequeue(&Q, &e) && e == -999);
    REQUIRE(!LinkQueueDequeue(&L, &e) && e == -999);
    REQUIRE(!QueuePeek(&Q, NULL) && !LinkQueuePeek(&L, NULL));
    REQUIRE(QueueEnqueueMany(&Q, NULL, 0));
    REQUIRE(!QueueEnqueueMany(&Q, NULL, 1));
    REQUIRE(!QueueEnqueueMany(&Q, &e, SIZE_MAX));
    REQUIRE(!QueueReserve(&Q, SIZE_MAX));
    for (int i = 1; i <= 4; ++i)
    {
        REQUIRE(QueueEnqueue(&Q, i) && LinkQueueEnqueue(&L, i));
    }
    REQUIRE(!LinkQueueInit(&L));
    for (int i = 1; i <= 2; ++i)
    {
        REQUIRE(QueueDequeue(&Q, &e) && e == i);
        REQUIRE(LinkQueueDequeue(&L, &e) && e == i);
    }
    REQUIRE(QueueEnqueue(&Q, 5) && LinkQueueEnqueue(&L, 5));
    REQUIRE(QueueEnqueue(&Q, 6) && LinkQueueEnqueue(&L, 6));
    int wrapped[] = {3, 4, 5, 6};
    Compare(&Q, &L, wrapped, 4);
    REQUIRE(Q.front == 2 && Q.size == Q.capacity);
#ifdef QUEUE_TEST_ALLOCATOR
    ElemType *oldData = Q.data;
    QueueNode *oldRear = L.rear;
    int oldLive = liveBlocks;
    failNext = 1;
    REQUIRE(!QueueEnqueue(&Q, 7) && Q.data == oldData && Q.front == 2);
    failNext = 1;
    REQUIRE(!QueueReserve(&Q, 8) && Q.data == oldData);
    int batch[] = {7, 8, 9};
    failNext = 1;
    REQUIRE(!QueueEnqueueMany(&Q, batch, 3) && Q.size == 4);
    failNext = 1;
    REQUIRE(!LinkQueueEnqueue(&L, 7) && L.rear == oldRear && L.size == 4);
    REQUIRE(liveBlocks == oldLive);
    Compare(&Q, &L, wrapped, 4);
#endif
    REQUIRE(QueueReserve(&Q, 8) && Q.front == 0);
    Compare(&Q, &L, wrapped, 4);
    int more[] = {7, 8, 9};
    REQUIRE(QueueEnqueueMany(&Q, more, 3));
    for (size_t i = 0; i < 3; ++i)
    {
        REQUIRE(LinkQueueEnqueue(&L, more[i]));
    }
    int seven[] = {3, 4, 5, 6, 7, 8, 9};
    Compare(&Q, &L, seven, 7);
    printf("Array queue (front first): ");
    QueuePrint(&Q);
    printf("Linked queue (front first): ");
    LinkQueuePrint(&L);
    REQUIRE(QueueReserve(&Q, Q.capacity));
    REQUIRE(QueueDequeue(&Q, NULL) && LinkQueueDequeue(&L, NULL));
    Compare(&Q, &L, seven + 1, 6);
    QueueClear(&Q);
    LinkQueueClear(&L);
    REQUIRE(Q.data != NULL && Q.size == 0 && Q.front == 0);
    Compare(&Q, &L, NULL, 0);
    REQUIRE(QueueEnqueue(&Q, 42) && LinkQueueEnqueue(&L, 42));
    REQUIRE(QueueDequeue(&Q, &e) && e == 42);
    REQUIRE(LinkQueueDequeue(&L, &e) && e == 42);
    Compare(&Q, &L, NULL, 0);
    REQUIRE(QueueEnqueue(&Q, 43) && LinkQueueEnqueue(&L, 43));
    QueueClear(&Q);
    LinkQueueClear(&L);

    int model[128];
    size_t n = 0;
    unsigned state = 20261010u;
    for (int step = 0; step < 1000; ++step)
    {
        state = state * 1664525u + 1013904223u;
        unsigned op = (state >> 16) % 4u;
        int value = (int)((state >> 8) % 101u) - 50;
        if ((op == 0 || op == 1) && n < 128)
        {
            REQUIRE(QueueEnqueue(&Q, value) && LinkQueueEnqueue(&L, value));
            model[n++] = value;
        }
        else if (op == 2 && n > 0)
        {
            REQUIRE(QueueDequeue(&Q, &e) && e == model[0]);
            REQUIRE(LinkQueueDequeue(&L, &e) && e == model[0]);
            for (size_t i = 1; i < n; ++i)
            {
                model[i - 1] = model[i];
            }
            --n;
        }
        else if (op == 3)
        {
            QueueClear(&Q);
            LinkQueueClear(&L);
            n = 0;
        }
        Compare(&Q, &L, model, n);
    }
    QueueDestroy(&Q);
    LinkQueueDestroy(&L);
    REQUIRE(Q.data == NULL && Q.size == 0 && Q.capacity == 0 && Q.front == 0);
    REQUIRE(L.front == NULL && L.rear == NULL && L.size == 0);
    QueueDestroy(&Q);
    LinkQueueDestroy(&L);
    QueueDestroy(NULL);
    LinkQueueDestroy(NULL);
    REQUIRE(QueueInit(&Q, 1) && QueueEnqueue(&Q, 7));
    REQUIRE(QueueDequeue(&Q, &e) && e == 7);
    REQUIRE(QueueEnqueue(&Q, 8) && QueueEnqueue(&Q, 9));
    REQUIRE(QueueDequeue(&Q, &e) && e == 8);
    REQUIRE(QueueDequeue(&Q, &e) && e == 9);
    QueueDestroy(&Q);
#ifdef QUEUE_TEST_ALLOCATOR
    REQUIRE(liveBlocks == 0);
    puts("Allocation failure and allocation/free balance checks passed.");
#endif
    puts("1000 array/linked-queue model checks passed.");
    puts("All Queue checks passed.");
    return 0;
}


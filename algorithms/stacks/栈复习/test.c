#include "Stack.h"
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

#ifdef STACK_TEST_ALLOCATOR
static int failNext = 0;
static int liveBlocks = 0;
void *StackTestMalloc(size_t bytes)
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
void StackTestFree(void *p)
{
    if (p != NULL)
    {
        REQUIRE(liveBlocks > 0);
        --liveBlocks;
    }
    free(p);
}
#endif

static void Compare(const Stack *S, const LinkStack *L, const int a[], size_t n)
{
    REQUIRE(StackLength(S) == n && LinkStackLength(L) == n);
    REQUIRE(StackEmpty(S) == (n == 0) && LinkStackEmpty(L) == (n == 0));
    REQUIRE(S->size <= S->capacity);
    const StackNode *p = L->top;
    for (size_t i = 0; i < n; ++i)
    {
        REQUIRE(S->data[i] == a[i]);
        REQUIRE(p != NULL && p->data == a[n - i - 1]);
        p = p->next;
    }
    REQUIRE(p == NULL);
    int e = -999;
    if (n > 0)
    {
        REQUIRE(StackPeek(S, &e) && e == a[n - 1]);
        REQUIRE(LinkStackPeek(L, &e) && e == a[n - 1]);
    }
    else
    {
        REQUIRE(!StackPeek(S, &e) && e == -999);
        REQUIRE(!LinkStackPeek(L, &e) && e == -999);
    }
}

int main(void)
{
    Stack S = {0};
    LinkStack L = {0};
    int e = -999;
    REQUIRE(!StackInit(NULL, 2) && !StackInit(&S, 0));
    REQUIRE(!StackInit(&S, SIZE_MAX));
    REQUIRE(!StackPush(&S, 1) && !StackReserve(&S, 1));
#ifdef STACK_TEST_ALLOCATOR
    failNext = 1;
    REQUIRE(!StackInit(&S, 2) && S.data == NULL);
#endif
    REQUIRE(StackInit(&S, 2) && LinkStackInit(&L));
    REQUIRE(!StackInit(&S, 2) && !LinkStackInit(NULL));
    REQUIRE(!StackPop(&S, &e) && e == -999);
    REQUIRE(!LinkStackPop(&L, &e) && e == -999);
    REQUIRE(!StackPeek(&S, NULL) && !LinkStackPeek(&L, NULL));
    REQUIRE(StackPushMany(&S, NULL, 0));
    REQUIRE(!StackPushMany(&S, NULL, 1));
    REQUIRE(!StackPushMany(&S, &e, SIZE_MAX));
    REQUIRE(!StackReserve(&S, SIZE_MAX));
    REQUIRE(StackPush(&S, 10) && StackPush(&S, 20));
    REQUIRE(LinkStackPush(&L, 10) && LinkStackPush(&L, 20));
    REQUIRE(!LinkStackInit(&L));
#ifdef STACK_TEST_ALLOCATOR
    ElemType *oldData = S.data;
    StackNode *oldTop = L.top;
    int oldLive = liveBlocks;
    failNext = 1;
    REQUIRE(!StackPush(&S, 30) && S.data == oldData && S.capacity == 2);
    failNext = 1;
    REQUIRE(!StackReserve(&S, 8) && S.data == oldData);
    int batch[] = {30, 40, 50};
    failNext = 1;
    REQUIRE(!StackPushMany(&S, batch, 3) && S.size == 2);
    failNext = 1;
    REQUIRE(!LinkStackPush(&L, 30) && L.top == oldTop && L.size == 2);
    REQUIRE(liveBlocks == oldLive);
#endif
    int two[] = {10, 20};
    Compare(&S, &L, two, 2);
    int more[] = {30, 40, 50};
    REQUIRE(StackPushMany(&S, more, 3));
    for (size_t i = 0; i < 3; ++i)
    {
        REQUIRE(LinkStackPush(&L, more[i]));
    }
    int five[] = {10, 20, 30, 40, 50};
    Compare(&S, &L, five, 5);
    printf("Array stack (top first): ");
    StackPrint(&S);
    printf("Linked stack (top first): ");
    LinkStackPrint(&L);
    REQUIRE(StackReserve(&S, S.capacity) && S.size == 5);
    REQUIRE(StackPop(&S, NULL) && LinkStackPop(&L, NULL));
    Compare(&S, &L, five, 4);
    StackClear(&S);
    LinkStackClear(&L);
    REQUIRE(S.data != NULL && S.size == 0 && L.top == NULL);
    Compare(&S, &L, NULL, 0);

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
            REQUIRE(StackPush(&S, value) && LinkStackPush(&L, value));
            model[n++] = value;
        }
        else if (op == 2 && n > 0)
        {
            REQUIRE(StackPop(&S, &e) && e == model[n - 1]);
            REQUIRE(LinkStackPop(&L, &e) && e == model[n - 1]);
            --n;
        }
        else if (op == 3)
        {
            StackClear(&S);
            LinkStackClear(&L);
            n = 0;
        }
        Compare(&S, &L, model, n);
    }
    StackDestroy(&S);
    LinkStackDestroy(&L);
    REQUIRE(S.data == NULL && S.size == 0 && S.capacity == 0);
    REQUIRE(L.top == NULL && L.size == 0);
    StackDestroy(&S);
    LinkStackDestroy(&L);
    StackDestroy(NULL);
    LinkStackDestroy(NULL);
    REQUIRE(StackInit(&S, 1) && StackPush(&S, 7));
    StackDestroy(&S);
#ifdef STACK_TEST_ALLOCATOR
    REQUIRE(liveBlocks == 0);
    puts("Allocation failure and allocation/free balance checks passed.");
#endif
    puts("1000 array/linked-stack model checks passed.");
    puts("All Stack checks passed.");
    return 0;
}


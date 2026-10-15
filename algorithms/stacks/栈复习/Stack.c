#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef STACK_TEST_ALLOCATOR
void *StackTestMalloc(size_t bytes);
void StackTestFree(void *p);
#define SMALLOC StackTestMalloc
#define SFREE StackTestFree
#else
#define SMALLOC malloc
#define SFREE free
#endif

/* 动态顺序栈。扩容只在新内存申请成功后提交更改。 */
int StackInit(Stack *S, size_t capacity)
{
    if (S == NULL || S->data != NULL || S->size != 0 || S->capacity != 0
        || capacity == 0 || capacity > SIZE_MAX / sizeof(ElemType))
    {
        return STACK_ERR;
    }
    ElemType *p = SMALLOC(capacity * sizeof(*p));
    if (p == NULL)
    {
        return STACK_ERR;
    }
    S->data = p;
    S->capacity = capacity;
    return STACK_OK;
}

int StackEmpty(const Stack *S)
{
    return S != NULL && S->size == 0;
}

size_t StackLength(const Stack *S)
{
    return S != NULL ? S->size : 0;
}

int StackPeek(const Stack *S, ElemType *e)
{
    if (S == NULL || S->size == 0 || e == NULL)
    {
        return STACK_ERR;
    }
    *e = S->data[S->size - 1];
    return STACK_OK;
}

int StackReserve(Stack *S, size_t capacity)
{
    if (S == NULL || S->data == NULL || capacity > SIZE_MAX / sizeof(ElemType))
    {
        return STACK_ERR;
    }
    if (capacity <= S->capacity)
    {
        return STACK_OK;
    }
    ElemType *p = SMALLOC(capacity * sizeof(*p));
    if (p == NULL)
    {
        return STACK_ERR;
    }
    if (S->size > 0)
    {
        memcpy(p, S->data, S->size * sizeof(*p));
    }
    SFREE(S->data);
    S->data = p;
    S->capacity = capacity;
    return STACK_OK;
}

static int EnsureCapacity(Stack *S, size_t needed)
{
    size_t limit = SIZE_MAX / sizeof(ElemType);
    size_t capacity = S->capacity;
    while (capacity < needed)
    {
        if (capacity > limit / 2)
        {
            capacity = needed;
            break;
        }
        capacity *= 2;
    }
    return StackReserve(S, capacity);
}

int StackPushMany(Stack *S, const ElemType a[], size_t n)
{
    if (S == NULL || S->data == NULL || (n > 0 && a == NULL)
        || n > SIZE_MAX / sizeof(ElemType) - S->size)
    {
        return STACK_ERR;
    }
    if (n == 0)
    {
        return STACK_OK;
    }
    if (!EnsureCapacity(S, S->size + n))
    {
        return STACK_ERR;
    }
    memcpy(S->data + S->size, a, n * sizeof(*a));
    S->size += n;
    return STACK_OK;
}

int StackPush(Stack *S, ElemType e)
{
    return StackPushMany(S, &e, 1);
}

int StackPop(Stack *S, ElemType *e)
{
    if (S == NULL || S->size == 0)
    {
        return STACK_ERR;
    }
    if (e != NULL)
    {
        *e = S->data[S->size - 1];
    }
    --S->size;
    return STACK_OK;
}

void StackClear(Stack *S)
{
    if (S != NULL)
    {
        S->size = 0;
    }
}

void StackDestroy(Stack *S)
{
    if (S != NULL)
    {
        SFREE(S->data);
        S->data = NULL;
        S->size = 0;
        S->capacity = 0;
    }
}

void StackPrint(const Stack *S)
{
    if (S == NULL)
    {
        return;
    }
    for (size_t i = S->size; i > 0; --i)
    {
        if (i != S->size)
        {
            printf(" ");
        }
        printf("%d", S->data[i - 1]);
    }
    printf("\n");
}

/* 链栈：头插、头删，不设置额外头结点。 */
int LinkStackInit(LinkStack *S)
{
    if (S == NULL || S->top != NULL || S->size != 0)
    {
        return STACK_ERR;
    }
    return STACK_OK;
}

int LinkStackEmpty(const LinkStack *S)
{
    return S != NULL && S->top == NULL;
}

size_t LinkStackLength(const LinkStack *S)
{
    return S != NULL ? S->size : 0;
}

int LinkStackPeek(const LinkStack *S, ElemType *e)
{
    if (S == NULL || S->top == NULL || e == NULL)
    {
        return STACK_ERR;
    }
    *e = S->top->data;
    return STACK_OK;
}

int LinkStackPush(LinkStack *S, ElemType e)
{
    if (S == NULL || S->size == SIZE_MAX)
    {
        return STACK_ERR;
    }
    StackNode *p = SMALLOC(sizeof(*p));
    if (p == NULL)
    {
        return STACK_ERR;
    }
    p->data = e;
    p->next = S->top;
    S->top = p;
    ++S->size;
    return STACK_OK;
}

int LinkStackPop(LinkStack *S, ElemType *e)
{
    if (S == NULL || S->top == NULL)
    {
        return STACK_ERR;
    }
    StackNode *p = S->top;
    if (e != NULL)
    {
        *e = p->data;
    }
    S->top = p->next;
    SFREE(p);
    --S->size;
    return STACK_OK;
}

void LinkStackClear(LinkStack *S)
{
    if (S != NULL)
    {
        while (LinkStackPop(S, NULL))
        {
            /* Pop 内部负责断链与释放。 */
        }
    }
}

void LinkStackDestroy(LinkStack *S)
{
    LinkStackClear(S);
}

void LinkStackPrint(const LinkStack *S)
{
    if (S == NULL)
    {
        return;
    }
    for (const StackNode *p = S->top; p != NULL; p = p->next)
    {
        if (p != S->top)
        {
            printf(" ");
        }
        printf("%d", p->data);
    }
    printf("\n");
}


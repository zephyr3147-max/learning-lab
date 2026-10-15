#include "SqList.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* 测试构建替换分配函数，以确定性模拟失败；普通构建直接用 realloc。 */
#ifdef SQLIST_TEST_ALLOCATOR
void *SqListTestRealloc(void *ptr, size_t bytes);
#define SQLIST_REALLOC SqListTestRealloc
#else
#define SQLIST_REALLOC realloc
#endif

/* ① 初始化：调用者先把结构体置零，失败时仍保持零状态。 */
int SqListInit(SqList *L)
{
    if (L == NULL || L->data != NULL)
    {
        return SQLIST_ERR;
    }
    return SqListReserve(L, SQLIST_INIT_CAPACITY);
}

/* capacity 以元素个数计，realloc 参数则以字节数计。 */
int SqListReserve(SqList *L, int minCapacity)
{
    if (L == NULL || minCapacity < 0)
    {
        return SQLIST_ERR;
    }
    if (minCapacity <= L->capacity)
    {
        return SQLIST_OK;
    }

    /* 同时防止 int 容量溢出，以及元素个数转字节数时 size_t 溢出。 */
    size_t maxElements = (size_t)-1 / sizeof(ElemType);
    int limit = INT_MAX;
    if (maxElements < (size_t)INT_MAX)
    {
        limit = (int)maxElements;
    }
    if (minCapacity > limit)
    {
        return SQLIST_ERR;
    }

    int newCapacity = L->capacity > 0 ? L->capacity : SQLIST_INIT_CAPACITY;
    while (newCapacity < minCapacity)
    {
        if (newCapacity > limit / 2)
        {
            newCapacity = minCapacity; /* 接近上限时不再翻倍，避免溢出 */
            break;
        }
        newCapacity *= 2;
    }

    ElemType *temp = SQLIST_REALLOC(L->data, (size_t)newCapacity * sizeof(*temp));
    if (temp == NULL)
    {
        return SQLIST_ERR; /* 原 data 仍有效，不能覆盖或 free 原指针 */
    }
    L->data = temp;
    L->capacity = newCapacity;
    return SQLIST_OK;
}

int SqListEmpty(const SqList *L)
{
    return L->length == 0;
}

int SqListFull(const SqList *L)
{
    return L->capacity > 0 && L->length == L->capacity;
}

int SqListLength(const SqList *L)
{
    return L->length;
}

int SqListCapacity(const SqList *L)
{
    return L->capacity;
}

/* ② 遍历：只访问 data[0..length-1]。 */
void SqListPrint(const SqList *L)
{
    for (int j = 0; j < L->length; ++j)
    {
        if (j > 0)
        {
            printf(" ");
        }
        printf("%d", L->data[j]);
    }
    printf("\n");
}

/* ③ 第 i 个元素的数组下标是 i-1。 */
int SqListGetElem(const SqList *L, int i, ElemType *outValue)
{
    if (outValue == NULL || i < 1 || i > L->length)
    {
        return SQLIST_ERR;
    }
    *outValue = L->data[i - 1];
    return SQLIST_OK;
}

int SqListSetElem(SqList *L, int i, ElemType value)
{
    if (i < 1 || i > L->length)
    {
        return SQLIST_ERR;
    }
    L->data[i - 1] = value;
    return SQLIST_OK;
}

/* ④ 按值查找：数组下标 j 转换成接口位置 j+1。 */
int SqListLocateElem(const SqList *L, ElemType value)
{
    for (int j = 0; j < L->length; ++j)
    {
        if (L->data[j] == value)
        {
            return j + 1;
        }
    }
    return 0;
}

int SqListPriorElem(const SqList *L, ElemType value, ElemType *outValue)
{
    int i = SqListLocateElem(L, value);
    if (i <= 1)
    {
        return SQLIST_ERR; /* 没找到，或第一个元素没有前驱 */
    }
    return SqListGetElem(L, i - 1, outValue);
}

int SqListNextElem(const SqList *L, ElemType value, ElemType *outValue)
{
    int i = SqListLocateElem(L, value);
    if (i == 0 || i == L->length)
    {
        return SQLIST_ERR;
    }
    return SqListGetElem(L, i + 1, outValue);
}

/* ⑤ 插入：从后往前搬，先给新元素腾出一格。 */
int SqListInsert(SqList *L, int i, ElemType value)
{
    if (L->length == INT_MAX || i < 1 || i > L->length + 1)
    {
        return SQLIST_ERR;
    }
    if (SqListReserve(L, L->length + 1) != SQLIST_OK)
    {
        return SQLIST_ERR;
    }

    for (int j = L->length; j >= i; --j)
    {
        L->data[j] = L->data[j - 1];
    }
    L->data[i - 1] = value;
    ++L->length;
    return SQLIST_OK;
}

int SqListPushBack(SqList *L, ElemType value)
{
    if (L->length == INT_MAX)
    {
        return SQLIST_ERR;
    }
    return SqListInsert(L, L->length + 1, value);
}

/* ⑥ 删除：后面的元素从前往后依次左移。 */
int SqListDelete(SqList *L, int i, ElemType *outValue)
{
    if (i < 1 || i > L->length)
    {
        return SQLIST_ERR;
    }

    if (outValue != NULL)
    {
        *outValue = L->data[i - 1];
    }
    for (int j = i; j < L->length; ++j)
    {
        L->data[j - 1] = L->data[j];
    }
    --L->length;
    return SQLIST_OK;
}

int SqListPopBack(SqList *L, ElemType *outValue)
{
    return SqListDelete(L, L->length, outValue);
}

/* ⑦ 从数组建表。校验通过后才覆盖已有内容。 */
int SqListAssign(SqList *L, const ElemType a[], int n)
{
    if (n < 0 || (n > 0 && a == NULL))
    {
        return SQLIST_ERR;
    }
    if (SqListReserve(L, n) != SQLIST_OK)
    {
        return SQLIST_ERR;
    }
    for (int j = 0; j < n; ++j)
    {
        L->data[j] = a[j];
    }
    L->length = n;
    return SQLIST_OK;
}

/* ⑧ 清空只是让旧数据不再属于有效区。 */
void SqListClear(SqList *L)
{
    L->length = 0;
}

void SqListDestroy(SqList *L)
{
    if (L == NULL)
    {
        return;
    }
    free(L->data);
    L->data = NULL;
    L->length = 0;
    L->capacity = 0;
}

/* ⑨ 扩展：首尾交换实现逆序。 */
void SqListReverse(SqList *L)
{
    int left = 0;
    int right = L->length - 1;
    while (left < right)
    {
        ElemType temp = L->data[left];
        L->data[left] = L->data[right];
        L->data[right] = temp;
        ++left;
        --right;
    }
}

/* 读指针扫描原表，写指针只保存要保留的值，保持相对顺序。 */
int SqListRemoveAll(SqList *L, ElemType value)
{
    int write = 0;
    int oldLength = L->length;
    for (int read = 0; read < oldLength; ++read)
    {
        if (L->data[read] != value)
        {
            L->data[write] = L->data[read];
            ++write;
        }
    }
    L->length = write;
    return oldLength - write;
}

/* 原表须有序：从尾向前找位置，同时搬动大于 value 的元素。 */
int SqListInsertOrdered(SqList *L, ElemType value)
{
    if (L->length == INT_MAX || SqListReserve(L, L->length + 1) != SQLIST_OK)
    {
        return SQLIST_ERR;
    }
    int j = L->length - 1;
    while (j >= 0 && L->data[j] > value)
    {
        L->data[j + 1] = L->data[j];
        --j;
    }
    L->data[j + 1] = value;
    ++L->length;
    return SQLIST_OK;
}

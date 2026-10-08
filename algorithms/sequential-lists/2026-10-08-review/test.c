#include "SqList.h"
#include <stdio.h>
#include <stdlib.h>

/* 仅测试构建启用：指定下一次分配失败，不需要真的耗尽内存。 */
#ifdef SQLIST_TEST_ALLOCATOR
static int failNextAllocation = 0;
void *SqListTestRealloc(void *ptr, size_t bytes)
{
    if (failNextAllocation)
    {
        failNextAllocation = 0;
        return NULL;
    }
    return realloc(ptr, bytes);
}
#endif

/* 普通函数执行检查，即使 Release 定义 NDEBUG 也不会跳过操作。 */
static void Require(int condition)
{
    if (!condition)
    {
        fprintf(stderr, "SqList check failed.\n");
        exit(EXIT_FAILURE);
    }
}

static void Check(const SqList *L, const ElemType expected[], int n)
{
    Require(SqListLength(L) == n);
    Require(SqListEmpty(L) == (n == 0));
    Require(n <= SqListCapacity(L));
    Require(SqListFull(L) == (L->capacity > 0 && n == L->capacity));
    for (int j = 0; j < n; ++j)
    {
        ElemType x = -1;
        Require(SqListGetElem(L, j + 1, &x) == SQLIST_OK);
        Require(x == expected[j]);
    }
}

int main(void)
{
    SqList L = {0};
    ElemType x = -123;
    Require(SqListInit(&L) == SQLIST_OK);
    Require(SqListInit(&L) == SQLIST_ERR); /* 活表不能重复初始化，否则可能泄漏 */
    Require(SqListInit(NULL) == SQLIST_ERR);
    Require(SqListCapacity(&L) == SQLIST_INIT_CAPACITY);
    Require(SqListReserve(&L, -1) == SQLIST_ERR);
    Require(SqListReserve(NULL, 1) == SQLIST_ERR);

    /* ① 空表和非法位置；失败不改变输出值。 */
    Check(&L, NULL, 0);
    Require(SqListLocateElem(&L, 10) == 0);
    Require(SqListGetElem(&L, 1, &x) == SQLIST_ERR && x == -123);
    Require(SqListGetElem(&L, 1, NULL) == SQLIST_ERR);
    Require(SqListSetElem(&L, 1, 1) == SQLIST_ERR);
    Require(SqListDelete(&L, 1, &x) == SQLIST_ERR && x == -123);
    Require(SqListPopBack(&L, &x) == SQLIST_ERR);
    Require(SqListInsert(&L, 0, 10) == SQLIST_ERR);
    Require(SqListInsert(&L, 2, 10) == SQLIST_ERR);
    Require(SqListPriorElem(&L, 10, &x) == SQLIST_ERR);
    Require(SqListNextElem(&L, 10, &x) == SQLIST_ERR);
    SqListReverse(&L);
    Require(SqListRemoveAll(&L, 1) == 0);
    Check(&L, NULL, 0);

    /* ② 头插、尾插、中间插。 */
    Require(SqListPushBack(&L, 20) == SQLIST_OK);
    Require(SqListInsert(&L, 1, 10) == SQLIST_OK);
    Require(SqListPushBack(&L, 40) == SQLIST_OK);
    Require(SqListInsert(&L, 3, 30) == SQLIST_OK);
    ElemType a[] = {10, 20, 30, 40};
    Check(&L, a, 4);
    printf("After insert: ");
    SqListPrint(&L);
    Require(SqListInsert(&L, 6, 99) == SQLIST_ERR);
    Check(&L, a, 4);

    /* ③ 取值、查找、前驱/后继与修改。 */
    Require(SqListGetElem(&L, 3, &x) == SQLIST_OK && x == 30);
    Require(SqListLocateElem(&L, 30) == 3);
    Require(SqListLocateElem(&L, 99) == 0);
    Require(SqListPriorElem(&L, 30, &x) == SQLIST_OK && x == 20);
    Require(SqListNextElem(&L, 30, &x) == SQLIST_OK && x == 40);
    Require(SqListPriorElem(&L, 10, &x) == SQLIST_ERR && x == 40);
    Require(SqListNextElem(&L, 40, &x) == SQLIST_ERR && x == 40);
    Require(SqListPriorElem(&L, 99, &x) == SQLIST_ERR);
    Require(SqListNextElem(&L, 99, &x) == SQLIST_ERR);
    Require(SqListPriorElem(&L, 30, NULL) == SQLIST_ERR);
    Require(SqListNextElem(&L, 30, NULL) == SQLIST_ERR);
    Require(SqListSetElem(&L, 2, 25) == SQLIST_OK);
    Require(SqListSetElem(&L, 0, 99) == SQLIST_ERR);
    Require(SqListSetElem(&L, 5, 99) == SQLIST_ERR);
    Require(SqListGetElem(&L, 0, &x) == SQLIST_ERR);
    Require(SqListGetElem(&L, 5, &x) == SQLIST_ERR);
    ElemType b[] = {10, 25, 30, 40};
    Check(&L, b, 4);

    /* ④ 中间删、头删、尾删、唯一元素删除，不取回值时传 NULL。 */
    Require(SqListDelete(&L, 2, &x) == SQLIST_OK && x == 25);
    ElemType c[] = {10, 30, 40};
    Check(&L, c, 3);
    printf("After delete: ");
    SqListPrint(&L);
    Require(SqListDelete(&L, 0, &x) == SQLIST_ERR && x == 25);
    Require(SqListDelete(&L, 4, &x) == SQLIST_ERR);
    Check(&L, c, 3);
    Require(SqListDelete(&L, 1, NULL) == SQLIST_OK);
    Require(SqListPopBack(&L, &x) == SQLIST_OK && x == 40);
    ElemType one[] = {30};
    Check(&L, one, 1);
    SqListReverse(&L);
    Check(&L, one, 1);
    Require(SqListPopBack(&L, NULL) == SQLIST_OK);
    Check(&L, NULL, 0);

    /* ⑤ 批量赋值与清空复用；非法赋值不覆盖原表。 */
    Require(SqListAssign(&L, a, 4) == SQLIST_OK);
    Require(SqListAssign(&L, a, -1) == SQLIST_ERR);
    Require(SqListAssign(&L, NULL, 1) == SQLIST_ERR);
    Check(&L, a, 4);
    SqListClear(&L);
    Check(&L, NULL, 0);
    Require(SqListPushBack(&L, 8) == SQLIST_OK);
    SqListDestroy(&L);
    SqListDestroy(&L);
    Check(&L, NULL, 0);
    Require(L.data == NULL && L.capacity == 0);
    SqListDestroy(NULL);
    Require(SqListInit(&L) == SQLIST_OK);
    Require(SqListAssign(&L, NULL, 0) == SQLIST_OK);

    /* ⑥ 表满后自动扩容，已有数据保持不变。 */
    ElemType full[SQLIST_INIT_CAPACITY];
    for (int j = 0; j < SQLIST_INIT_CAPACITY; ++j)
    {
        full[j] = j;
        Require(SqListPushBack(&L, j) == SQLIST_OK);
    }
    Check(&L, full, SQLIST_INIT_CAPACITY);

#ifdef SQLIST_TEST_ALLOCATOR
    ElemType *oldData = L.data;
    failNextAllocation = 1;
    Require(SqListReserve(&L, L.capacity + 1) == SQLIST_ERR);
    Require(L.data == oldData && L.capacity == SQLIST_INIT_CAPACITY);
    Check(&L, full, SQLIST_INIT_CAPACITY);
    failNextAllocation = 1;
    Require(SqListInsert(&L, 1, 999) == SQLIST_ERR);
    Check(&L, full, SQLIST_INIT_CAPACITY);
    failNextAllocation = 1;
    Require(SqListPushBack(&L, 999) == SQLIST_ERR);
    Check(&L, full, SQLIST_INIT_CAPACITY);
    failNextAllocation = 1;
    Require(SqListInsertOrdered(&L, 999) == SQLIST_ERR);
    Require(L.data == oldData && L.capacity == SQLIST_INIT_CAPACITY);
    Check(&L, full, SQLIST_INIT_CAPACITY);
#endif

    Require(SqListInsert(&L, 1, -1) == SQLIST_OK);
    Require(L.capacity == 2 * SQLIST_INIT_CAPACITY);
    ElemType afterGrowth[SQLIST_INIT_CAPACITY + 1];
    afterGrowth[0] = -1;
    for (int j = 0; j < SQLIST_INIT_CAPACITY; ++j)
    {
        afterGrowth[j + 1] = j;
    }
    Check(&L, afterGrowth, SQLIST_INIT_CAPACITY + 1);
    Require(SqListDelete(&L, 1, &x) == SQLIST_OK && x == -1);
    Check(&L, full, SQLIST_INIT_CAPACITY);

    /* 多次尾插跨越 200/400 容量边界；Get 检查全部旧值。 */
    for (int j = SQLIST_INIT_CAPACITY; j < 501; ++j)
    {
        Require(SqListPushBack(&L, j) == SQLIST_OK);
    }
    ElemType many[501];
    for (int j = 0; j < 501; ++j)
    {
        many[j] = j;
    }
    Check(&L, many, 501);
    Require(L.capacity == 800);
    int savedCapacity = L.capacity;
    ElemType *savedData = L.data;
    Require(SqListReserve(&L, 501) == SQLIST_OK);
    Require(L.data == savedData && L.capacity == savedCapacity);
    SqListClear(&L);
    Require(L.data == savedData && L.capacity == savedCapacity);
    Check(&L, NULL, 0);

    /* 批量赋值也会扩容；失败保留原表。 */
    SqListDestroy(&L);
    Require(SqListInit(&L) == SQLIST_OK);
    Require(SqListAssign(&L, a, 4) == SQLIST_OK);
#ifdef SQLIST_TEST_ALLOCATOR
    savedData = L.data;
    failNextAllocation = 1;
    Require(SqListAssign(&L, many, 501) == SQLIST_ERR);
    Require(L.data == savedData && L.capacity == SQLIST_INIT_CAPACITY);
    Check(&L, a, 4);
#endif
    Require(SqListAssign(&L, many, 501) == SQLIST_OK);
    Check(&L, many, 501);
    Require(L.capacity == 800);
    printf("Auto growth: length=%d capacity=%d\n", L.length, L.capacity);

    /* 有序插入在表满时扩容，结果继续保持有序。 */
    SqListDestroy(&L);
    Require(SqListInit(&L) == SQLIST_OK);
    Require(SqListAssign(&L, full, SQLIST_INIT_CAPACITY) == SQLIST_OK);
    Require(SqListInsertOrdered(&L, SQLIST_INIT_CAPACITY) == SQLIST_OK);
    for (int j = 0; j <= SQLIST_INIT_CAPACITY; ++j)
    {
        afterGrowth[j] = j;
    }
    Check(&L, afterGrowth, SQLIST_INIT_CAPACITY + 1);
    Require(L.capacity == 2 * SQLIST_INIT_CAPACITY);

    /* ⑦ 逆序两次还原；读写指针删除重复值，保持保留值的顺序。 */
    Require(SqListAssign(&L, a, 4) == SQLIST_OK);
    SqListReverse(&L);
    ElemType reversed[] = {40, 30, 20, 10};
    Check(&L, reversed, 4);
    SqListReverse(&L);
    Check(&L, a, 4);
    ElemType repeated[] = {2, 1, 2, 3, 2};
    Require(SqListAssign(&L, repeated, 5) == SQLIST_OK);
    Require(SqListLocateElem(&L, 2) == 1);
    Require(SqListRemoveAll(&L, 2) == 3);
    ElemType kept[] = {1, 3};
    Check(&L, kept, 2);
    Require(SqListRemoveAll(&L, 99) == 0);
    Check(&L, kept, 2);
    ElemType same[] = {7, 7, 7};
    Require(SqListAssign(&L, same, 3) == SQLIST_OK);
    Require(SqListRemoveAll(&L, 7) == 3);
    Check(&L, NULL, 0);

    /* ⑧ 有序插入：空表、最前、最后、中间和重复值。 */
    Require(SqListInsertOrdered(&L, 20) == SQLIST_OK);
    Require(SqListInsertOrdered(&L, 10) == SQLIST_OK);
    Require(SqListInsertOrdered(&L, 40) == SQLIST_OK);
    Require(SqListInsertOrdered(&L, 30) == SQLIST_OK);
    Require(SqListInsertOrdered(&L, 20) == SQLIST_OK);
    Require(SqListInsertOrdered(&L, -5) == SQLIST_OK);
    ElemType ordered[] = {-5, 10, 20, 20, 30, 40};
    Check(&L, ordered, 6);
    printf("Ordered insert: ");
    SqListPrint(&L);
    SqListDestroy(&L);
    Require(L.data == NULL && L.length == 0 && L.capacity == 0);
#ifdef SQLIST_TEST_ALLOCATOR
    failNextAllocation = 1;
    Require(SqListInit(&L) == SQLIST_ERR);
    Require(L.data == NULL && L.length == 0 && L.capacity == 0);
    Require(SqListInit(&L) == SQLIST_OK);
    SqListDestroy(&L);
    printf("Allocation failure checks passed.\n");
#endif
    printf("All SqList checks passed.\n");
    return 0;
}

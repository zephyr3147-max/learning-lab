#include "SList.h"
#include <stdio.h>
#include <stdlib.h>

static void Require(int condition, const char *expression, int line)
{
    if (!condition)
    {
        fprintf(stderr, "Check failed at line %d: %s\n", line, expression);
        exit(EXIT_FAILURE);
    }
}
#define REQUIRE(condition) Require((condition), #condition, __LINE__)

#ifdef SLIST_TEST_ALLOCATOR
static int failAfter = -1;
void *SListTestMalloc(size_t bytes)
{
    if (failAfter == 0)
    {
        failAfter = -1;
        return NULL;
    }
    if (failAfter > 0)
    {
        --failAfter;
    }
    return malloc(bytes);
}
#endif

/* 先有限步检查结点与末尾，再求长度，避免坏环导致检查无限遍历。 */
static void Check(const SListNode *L, const ElemType expected[], int n)
{
    REQUIRE(L != NULL);
    const SListNode *p = L->next;
    for (int i = 0; i < n; ++i)
    {
        REQUIRE(p != NULL);
        REQUIRE(p->data == expected[i]);
        p = p->next;
    }
    REQUIRE(p == NULL);
    REQUIRE(SListLength(L) == n);
    REQUIRE(SListEmpty(L) == (n == 0));
    ElemType x = -999;
    for (int i = 0; i < n; ++i)
    {
        REQUIRE(SListGetElem(L, i + 1, &x) == SLIST_OK);
        REQUIRE(x == expected[i]);
    }
    x = -999;
    REQUIRE(SListGetElem(L, n + 1, &x) == SLIST_ERR && x == -999);
}

/* 小型数组模型核对 1000 次确定性操作，无测试框架。 */
static void ModelChecks(LinkList L)
{
    ElemType model[128];
    int n = 0;
    unsigned state = 20261008u;
    SListClear(L);
    for (int step = 0; step < 1000; ++step)
    {
        state = state * 1664525u + 1013904223u;
        int op = (int)(state % 5u);
        ElemType value = (int)((state >> 8) % 11u) - 5;
        if (op == 0 && n < 128)
        {
            int position = (int)((state >> 16) % (unsigned)(n + 1)) + 1;
            REQUIRE(SListInsert(L, position, value) == SLIST_OK);
            for (int j = n; j >= position; --j)
            {
                model[j] = model[j - 1];
            }
            model[position - 1] = value;
            ++n;
        }
        else if (op == 1 && n > 0)
        {
            int position = (int)((state >> 16) % (unsigned)n) + 1;
            ElemType removed;
            REQUIRE(SListDelete(L, position, &removed) == SLIST_OK);
            REQUIRE(removed == model[position - 1]);
            for (int j = position; j < n; ++j)
            {
                model[j - 1] = model[j];
            }
            --n;
        }
        else if (op == 2)
        {
            SListReverse(L);
            for (int left = 0, right = n - 1; left < right; ++left, --right)
            {
                ElemType temp = model[left];
                model[left] = model[right];
                model[right] = temp;
            }
        }
        else if (op == 3)
        {
            int write = 0;
            for (int read = 0; read < n; ++read)
            {
                if (model[read] != value)
                {
                    model[write++] = model[read];
                }
            }
            REQUIRE(SListRemoveAll(L, value) == n - write);
            n = write;
        }
        else if (n > 0)
        {
            int position = (int)((state >> 16) % (unsigned)n) + 1;
            REQUIRE(SListSetElem(L, position, value) == SLIST_OK);
            model[position - 1] = value;
        }
        Check(L, model, n);
    }
    puts("Array-model checks passed.");
}

int main(void)
{
    LinkList L = NULL;
    ElemType x = -999;
    REQUIRE(SListInit(NULL) == SLIST_ERR);
#ifdef SLIST_TEST_ALLOCATOR
    failAfter = 0;
    REQUIRE(SListInit(&L) == SLIST_ERR && L == NULL);
#endif
    REQUIRE(SListInit(&L) == SLIST_OK);
    SListNode *head = L;
    REQUIRE(SListInit(&L) == SLIST_ERR && L == head);
    Check(L, NULL, 0);
    REQUIRE(SListEmpty(NULL) == 0 && SListLength(NULL) == 0);
    REQUIRE(SListGetElem(NULL, 1, &x) == SLIST_ERR && x == -999);
    REQUIRE(SListGetElem(L, 0, &x) == SLIST_ERR && x == -999);
    REQUIRE(SListGetElem(L, 1, NULL) == SLIST_ERR);
    REQUIRE(SListSetElem(L, 1, 10) == SLIST_ERR);
    REQUIRE(SListLocateElem(L, 10) == 0);
    REQUIRE(SListPriorElem(L, 10, &x) == SLIST_ERR && x == -999);
    REQUIRE(SListNextElem(L, 10, &x) == SLIST_ERR && x == -999);
    REQUIRE(SListInsert(L, 0, 10) == SLIST_ERR);
    REQUIRE(SListInsert(L, 2, 10) == SLIST_ERR);
    REQUIRE(SListInsert(NULL, 1, 10) == SLIST_ERR);
    REQUIRE(SListDelete(L, 1, &x) == SLIST_ERR && x == -999);
    REQUIRE(SListPopFront(L, &x) == SLIST_ERR && x == -999);
    REQUIRE(SListPopBack(L, &x) == SLIST_ERR && x == -999);
    REQUIRE(SListDeleteValue(L, 10) == SLIST_ERR);
    REQUIRE(SListRemoveAll(L, 10) == 0);
    REQUIRE(SListMiddle(L, &x) == SLIST_ERR && x == -999);
    REQUIRE(SListKthFromEnd(L, 1, &x) == SLIST_ERR && x == -999);
    REQUIRE(SListAssign(L, NULL, 1) == SLIST_ERR);
    REQUIRE(SListAssign(L, NULL, -1) == SLIST_ERR);
    SListReverse(L);
    Check(L, NULL, 0);

    ElemType a[] = {10, 20, 30, 40};
    REQUIRE(SListAssign(L, a, 4) == SLIST_OK);
    Check(L, a, 4);
    printf("After assign: ");
    SListPrint(L);
    REQUIRE(SListLocateElem(L, 20) == 2);
    REQUIRE(SListPriorElem(L, 20, &x) == SLIST_OK && x == 10);
    REQUIRE(SListNextElem(L, 20, &x) == SLIST_OK && x == 30);
    x = -999;
    REQUIRE(SListPriorElem(L, 10, &x) == SLIST_ERR && x == -999);
    REQUIRE(SListNextElem(L, 40, &x) == SLIST_ERR && x == -999);
    REQUIRE(SListPriorElem(L, 99, &x) == SLIST_ERR && x == -999);
    REQUIRE(SListNextElem(L, 99, &x) == SLIST_ERR && x == -999);
    REQUIRE(SListPriorElem(L, 20, NULL) == SLIST_ERR);
    REQUIRE(SListNextElem(L, 20, NULL) == SLIST_ERR);
    REQUIRE(SListSetElem(L, 2, 25) == SLIST_OK);
    REQUIRE(SListGetElem(L, 2, &x) == SLIST_OK && x == 25);
    REQUIRE(SListSetElem(L, 2, 20) == SLIST_OK);
    REQUIRE(SListSetElem(L, 5, 99) == SLIST_ERR);
    REQUIRE(SListInsert(L, 6, 99) == SLIST_ERR);
    REQUIRE(SListDelete(L, 0, NULL) == SLIST_ERR);
    REQUIRE(SListDelete(L, 5, NULL) == SLIST_ERR);
    Check(L, a, 4);

#ifdef SLIST_TEST_ALLOCATOR
    SListNode *first = L->next;
    failAfter = 0;
    REQUIRE(SListInsert(L, 2, 99) == SLIST_ERR);
    REQUIRE(L->next == first);
    Check(L, a, 4);
    failAfter = 0;
    REQUIRE(SListPushFront(L, 99) == SLIST_ERR);
    failAfter = 0;
    REQUIRE(SListPushBack(L, 99) == SLIST_ERR);
    Check(L, a, 4);
    ElemType replacement[] = {1, 2, 3, 4, 5};
    for (int point = 0; point < 5; ++point)
    {
        failAfter = point;
        REQUIRE(SListAssign(L, replacement, 5) == SLIST_ERR);
        REQUIRE(L == head && L->next == first);
        Check(L, a, 4);
    }
    puts("Allocation failure checks passed.");
#endif

    REQUIRE(SListPushFront(L, 5) == SLIST_OK);
    REQUIRE(SListPushBack(L, 50) == SLIST_OK);
    REQUIRE(SListInsert(L, 3, 15) == SLIST_OK);
    ElemType inserted[] = {5, 10, 15, 20, 30, 40, 50};
    Check(L, inserted, 7);
    printf("After insert: ");
    SListPrint(L);
    REQUIRE(SListDelete(L, 1, &x) == SLIST_OK && x == 5);
    REQUIRE(SListPopBack(L, &x) == SLIST_OK && x == 50);
    REQUIRE(SListDelete(L, 3, &x) == SLIST_OK && x == 20);
    REQUIRE(SListPopFront(L, &x) == SLIST_OK && x == 10);
    ElemType deleted[] = {15, 30, 40};
    Check(L, deleted, 3);
    printf("After delete: ");
    SListPrint(L);
    SListReverse(L);
    ElemType reversed[] = {40, 30, 15};
    Check(L, reversed, 3);
    printf("After reverse: ");
    SListPrint(L);
    SListReverse(L);
    Check(L, deleted, 3);
    REQUIRE(SListDeleteValue(L, 30) == SLIST_OK);
    REQUIRE(SListDeleteValue(L, 99) == SLIST_ERR);
    ElemType remaining[] = {15, 40};
    Check(L, remaining, 2);

    ElemType repeated[] = {2, 2, 1, 2, 3, 2};
    REQUIRE(SListAssign(L, repeated, 6) == SLIST_OK);
    REQUIRE(SListLocateElem(L, 2) == 1);
    REQUIRE(SListNextElem(L, 2, &x) == SLIST_OK && x == 2);
    x = -999;
    REQUIRE(SListPriorElem(L, 2, &x) == SLIST_ERR && x == -999);
    REQUIRE(SListDeleteValue(L, 2) == SLIST_OK);
    ElemType once[] = {2, 1, 2, 3, 2};
    Check(L, once, 5);
    REQUIRE(SListRemoveAll(L, 2) == 3);
    ElemType kept[] = {1, 3};
    Check(L, kept, 2);
    REQUIRE(SListRemoveAll(L, 99) == 0);
    REQUIRE(SListRemoveAll(L, 1) == 1 && SListRemoveAll(L, 3) == 1);
    Check(L, NULL, 0);
    REQUIRE(SListPushBack(L, 8) == SLIST_OK);
    REQUIRE(SListPopBack(L, NULL) == SLIST_OK);
    Check(L, NULL, 0);

    ElemType numbers[] = {1, 2, 3, 4, 5};
    REQUIRE(SListAssign(L, numbers, 5) == SLIST_OK);
    REQUIRE(SListMiddle(L, &x) == SLIST_OK && x == 3);
    REQUIRE(SListKthFromEnd(L, 2, &x) == SLIST_OK && x == 4);
    printf("Middle=3, kth-from-end(2)=%d\n", x);
    REQUIRE(SListKthFromEnd(L, 1, &x) == SLIST_OK && x == 5);
    REQUIRE(SListKthFromEnd(L, 5, &x) == SLIST_OK && x == 1);
    x = -999;
    REQUIRE(SListKthFromEnd(L, 0, &x) == SLIST_ERR && x == -999);
    REQUIRE(SListKthFromEnd(L, 6, &x) == SLIST_ERR && x == -999);
    REQUIRE(SListKthFromEnd(L, 2, NULL) == SLIST_ERR);
    REQUIRE(SListMiddle(L, NULL) == SLIST_ERR);
    REQUIRE(SListAssign(L, numbers, 4) == SLIST_OK);
    REQUIRE(SListMiddle(L, &x) == SLIST_OK && x == 3);
    REQUIRE(SListAssign(L, numbers, 1) == SLIST_OK);
    REQUIRE(SListMiddle(L, &x) == SLIST_OK && x == 1);
    SListReverse(L);
    Check(L, numbers, 1);
    REQUIRE(SListAssign(L, NULL, 0) == SLIST_OK);
    REQUIRE(L == head);
    Check(L, NULL, 0);

    LinkList A = NULL, B = NULL, C = NULL;
    REQUIRE(SListInit(&A) == SLIST_OK);
    REQUIRE(SListInit(&B) == SLIST_OK);
    REQUIRE(SListInit(&C) == SLIST_OK);
    ElemType av[] = {1, 3, 3, 7};
    ElemType bv[] = {2, 3, 8};
    REQUIRE(SListAssign(A, av, 4) == SLIST_OK);
    REQUIRE(SListAssign(B, bv, 3) == SLIST_OK);
    REQUIRE(SListMergeSorted(A, A, B) == SLIST_ERR);
    REQUIRE(SListMergeSorted(C, A, A) == SLIST_ERR);
    REQUIRE(SListMergeSorted(NULL, A, B) == SLIST_ERR);
    Check(A, av, 4);
    Check(B, bv, 3);
    SListNode *aFirstThree = A->next->next;
    SListNode *aSecondThree = aFirstThree->next;
    SListNode *bThree = B->next->next;
#ifdef SLIST_TEST_ALLOCATOR
    failAfter = 0;
#endif
    REQUIRE(SListMergeSorted(C, A, B) == SLIST_OK);
#ifdef SLIST_TEST_ALLOCATOR
    REQUIRE(failAfter == 0); /* 合并完全没有申请新结点。 */
    failAfter = -1;
#endif
    ElemType merged[] = {1, 2, 3, 3, 3, 7, 8};
    Check(C, merged, 7);
    Check(A, NULL, 0);
    Check(B, NULL, 0);
    REQUIRE(C->next->next->next == aFirstThree);
    REQUIRE(aFirstThree->next == aSecondThree && aSecondThree->next == bThree);
    printf("After merge: ");
    SListPrint(C);
    REQUIRE(SListMergeSorted(C, A, B) == SLIST_ERR);
    Check(C, merged, 7);
    SListClear(C);
    ElemType unsorted[] = {3, 1};
    REQUIRE(SListAssign(A, unsorted, 2) == SLIST_OK);
    REQUIRE(SListAssign(B, bv, 3) == SLIST_OK);
    REQUIRE(SListMergeSorted(C, A, B) == SLIST_ERR);
    Check(A, unsorted, 2);
    Check(B, bv, 3);
    Check(C, NULL, 0);
    SListClear(A);
    REQUIRE(SListMergeSorted(C, A, B) == SLIST_OK);
    Check(C, bv, 3);
    Check(B, NULL, 0);
    SListClear(C);
    REQUIRE(SListMergeSorted(C, A, B) == SLIST_OK);
    Check(C, NULL, 0);
    SListDestroy(&A);
    SListDestroy(&B);
    SListDestroy(&C);
    REQUIRE(A == NULL && B == NULL && C == NULL);

    ModelChecks(L);
    SListClear(L);
    REQUIRE(L == head);
    Check(L, NULL, 0);
    SListDestroy(&L);
    REQUIRE(L == NULL);
    SListDestroy(&L);
    SListDestroy(NULL);
    SListClear(NULL);
    SListReverse(NULL);
    REQUIRE(SListInit(&L) == SLIST_OK);
    SListDestroy(&L);
    puts("All SList checks passed.");
    return 0;
}

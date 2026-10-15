#include "DList.h"
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

#ifdef DLIST_TEST_ALLOCATOR
static int failAfter = -1;
static int liveNodes = 0;
void *DListTestMalloc(size_t bytes)
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
    void *ptr = malloc(bytes);
    if (ptr != NULL)
    {
        ++liveNodes;
    }
    return ptr;
}
void DListTestFree(void *ptr)
{
    if (ptr != NULL)
    {
        REQUIRE(liveNodes > 0);
        --liveNodes;
    }
    free(ptr);
}
#endif

/* 正反向都走恰好 n 个结点，再确认回到同一头结点。 */
static void Check(DLinkList L, const ElemType expected[], int n)
{
    REQUIRE(L != NULL && L->next != NULL && L->prev != NULL);
    REQUIRE(L->next->prev == L && L->prev->next == L);
    const DListNode *p = L->next;
    for (int i = 0; i < n; ++i)
    {
        REQUIRE(p != NULL && p != L);
        REQUIRE(p->data == expected[i]);
        REQUIRE(p->next != NULL && p->prev != NULL);
        REQUIRE(p->next->prev == p && p->prev->next == p);
        p = p->next;
    }
    REQUIRE(p == L);
    p = L->prev;
    for (int i = n - 1; i >= 0; --i)
    {
        REQUIRE(p != NULL && p != L && p->data == expected[i]);
        p = p->prev;
    }
    REQUIRE(p == L);
    REQUIRE(DListEmpty(L) == (n == 0) && DListLength(L) == n);
    ElemType x = -999;
    for (int i = 0; i < n; ++i)
    {
        REQUIRE(DListGetElem(L, i + 1, &x) == DLIST_OK && x == expected[i]);
        REQUIRE(DListGetFromBack(L, i + 1, &x) == DLIST_OK && x == expected[n - 1 - i]);
        REQUIRE(DListGetNode(L, i + 1)->data == expected[i]);
    }
    x = -999;
    REQUIRE(DListGetElem(L, n + 1, &x) == DLIST_ERR && x == -999);
    REQUIRE(DListGetFromBack(L, n + 1, &x) == DLIST_ERR && x == -999);
    REQUIRE(DListGetNode(L, n + 1) == NULL);
}

static void ModelChecks(DLinkList L)
{
    ElemType model[128];
    int n = 0;
    unsigned state = 20261010u;
    DListClear(L);
    for (int step = 0; step < 1000; ++step)
    {
        state = state * 1664525u + 1013904223u;
        int op = (int)(state % 8u);
        ElemType value = (int)((state >> 8) % 11u) - 5;
        if ((op == 0 || op == 5 || op == 6) && n < 128)
        {
            int position = (int)((state >> 16) % (unsigned)(n + 1)) + 1;
            if (op == 5)
            {
                position = 1;
                REQUIRE(DListPushFront(L, value) == DLIST_OK);
            }
            else if (op == 6)
            {
                position = n + 1;
                REQUIRE(DListPushBack(L, value) == DLIST_OK);
            }
            else
            {
                REQUIRE(DListInsert(L, position, value) == DLIST_OK);
            }
            for (int j = n; j >= position; --j)
            {
                model[j] = model[j - 1];
            }
            model[position - 1] = value;
            ++n;
        }
        else if ((op == 1 || op == 7) && n > 0)
        {
            int position = (int)((state >> 16) % (unsigned)n) + 1;
            ElemType x;
            if (op == 7)
            {
                position = n;
                REQUIRE(DListPopBack(L, &x) == DLIST_OK);
            }
            else
            {
                REQUIRE(DListDelete(L, position, &x) == DLIST_OK);
            }
            REQUIRE(x == model[position - 1]);
            for (int j = position; j < n; ++j)
            {
                model[j - 1] = model[j];
            }
            --n;
        }
        else if (op == 2)
        {
            DListReverse(L);
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
            REQUIRE(DListRemoveAll(L, value) == n - write);
            n = write;
        }
        else if (n > 0)
        {
            int position = (int)((state >> 16) % (unsigned)n) + 1;
            REQUIRE(DListSetElem(L, position, value) == DLIST_OK);
            model[position - 1] = value;
        }
        Check(L, model, n);
    }
    puts("1000 array-model and bidirectional-link checks passed.");
}

int main(void)
{
    DLinkList L = NULL;
    ElemType x = -999;
    REQUIRE(DListInit(NULL) == DLIST_ERR);
#ifdef DLIST_TEST_ALLOCATOR
    failAfter = 0;
    REQUIRE(DListInit(&L) == DLIST_ERR && L == NULL && liveNodes == 0);
#endif
    REQUIRE(DListInit(&L) == DLIST_OK);
    DListNode *head = L;
    REQUIRE(DListInit(&L) == DLIST_ERR && L == head);
    Check(L, NULL, 0);
    REQUIRE(DListEmpty(NULL) == 0 && DListLength(NULL) == 0);
    REQUIRE(DListGetElem(NULL, 1, &x) == DLIST_ERR && x == -999);
    REQUIRE(DListGetElem(L, 0, &x) == DLIST_ERR && x == -999);
    REQUIRE(DListGetElem(L, 1, NULL) == DLIST_ERR);
    REQUIRE(DListGetNode(L, 0) == NULL);
    REQUIRE(DListSetElem(L, 1, 10) == DLIST_ERR);
    REQUIRE(DListLocateElem(L, 10) == 0);
    REQUIRE(DListPriorElem(L, 10, &x) == DLIST_ERR && x == -999);
    REQUIRE(DListNextElem(L, 10, &x) == DLIST_ERR && x == -999);
    REQUIRE(DListInsert(L, 0, 10) == DLIST_ERR);
    REQUIRE(DListInsert(L, 2, 10) == DLIST_ERR);
    REQUIRE(DListInsert(NULL, 1, 10) == DLIST_ERR);
    REQUIRE(DListInsertBefore(NULL, 10) == DLIST_ERR);
    REQUIRE(DListErase(L, L, &x) == DLIST_ERR && x == -999);
    REQUIRE(DListErase(L, NULL, &x) == DLIST_ERR && x == -999);
    REQUIRE(DListDelete(L, 1, &x) == DLIST_ERR && x == -999);
    REQUIRE(DListPopFront(L, &x) == DLIST_ERR && x == -999);
    REQUIRE(DListPopBack(L, &x) == DLIST_ERR && x == -999);
    REQUIRE(DListGetFromBack(L, 0, &x) == DLIST_ERR && x == -999);
    REQUIRE(DListDeleteValue(L, 10) == DLIST_ERR);
    REQUIRE(DListRemoveAll(L, 10) == 0);
    REQUIRE(DListAssign(L, NULL, 1) == DLIST_ERR);
    REQUIRE(DListAssign(L, NULL, -1) == DLIST_ERR);
    DListReverse(L);
    Check(L, NULL, 0);

    ElemType a[] = {10, 20, 30, 40};
    REQUIRE(DListAssign(L, a, 4) == DLIST_OK);
    Check(L, a, 4);
    printf("Forward: ");
    DListPrint(L);
    printf("Backward: ");
    DListPrintReverse(L);
    REQUIRE(DListLocateElem(L, 20) == 2);
    REQUIRE(DListPriorElem(L, 20, &x) == DLIST_OK && x == 10);
    REQUIRE(DListNextElem(L, 20, &x) == DLIST_OK && x == 30);
    x = -999;
    REQUIRE(DListPriorElem(L, 10, &x) == DLIST_ERR && x == -999);
    REQUIRE(DListNextElem(L, 40, &x) == DLIST_ERR && x == -999);
    REQUIRE(DListPriorElem(L, 99, &x) == DLIST_ERR && x == -999);
    REQUIRE(DListNextElem(L, 99, &x) == DLIST_ERR && x == -999);
    REQUIRE(DListPriorElem(L, 20, NULL) == DLIST_ERR);
    REQUIRE(DListNextElem(L, 20, NULL) == DLIST_ERR);
    REQUIRE(DListSetElem(L, 2, 25) == DLIST_OK);
    REQUIRE(DListGetElem(L, 2, &x) == DLIST_OK && x == 25);
    REQUIRE(DListSetElem(L, 2, 20) == DLIST_OK);
    REQUIRE(DListSetElem(L, 5, 99) == DLIST_ERR);
    REQUIRE(DListInsert(L, 6, 99) == DLIST_ERR);
    REQUIRE(DListDelete(L, 0, NULL) == DLIST_ERR);
    REQUIRE(DListDelete(L, 5, NULL) == DLIST_ERR);
    Check(L, a, 4);

#ifdef DLIST_TEST_ALLOCATOR
    DListNode *first = L->next;
    DListNode *last = L->prev;
    int oldLive = liveNodes;
    failAfter = 0;
    REQUIRE(DListInsert(L, 2, 99) == DLIST_ERR);
    failAfter = 0;
    REQUIRE(DListPushFront(L, 99) == DLIST_ERR);
    failAfter = 0;
    REQUIRE(DListPushBack(L, 99) == DLIST_ERR);
    failAfter = 0;
    REQUIRE(DListInsertBefore(first, 99) == DLIST_ERR);
    failAfter = 0;
    REQUIRE(DListInsertOrdered(L, 99) == DLIST_ERR);
    ElemType replacement[] = {1, 2, 3, 4, 5};
    for (int point = 0; point < 5; ++point)
    {
        failAfter = point;
        REQUIRE(DListAssign(L, replacement, 5) == DLIST_ERR);
        REQUIRE(L == head && L->next == first && L->prev == last);
        REQUIRE(liveNodes == oldLive);
        Check(L, a, 4);
    }
#endif

    REQUIRE(DListPushFront(L, 5) == DLIST_OK);
    REQUIRE(DListPushBack(L, 50) == DLIST_OK);
    REQUIRE(DListInsertBefore(DListGetNode(L, 3), 15) == DLIST_OK);
    ElemType inserted[] = {5, 10, 15, 20, 30, 40, 50};
    Check(L, inserted, 7);
    REQUIRE(DListPopFront(L, &x) == DLIST_OK && x == 5);
    REQUIRE(DListPopBack(L, &x) == DLIST_OK && x == 50);
    REQUIRE(DListErase(L, DListGetNode(L, 3), &x) == DLIST_OK && x == 20);
    ElemType deleted[] = {10, 15, 30, 40};
    Check(L, deleted, 4);
    DListReverse(L);
    ElemType reversed[] = {40, 30, 15, 10};
    Check(L, reversed, 4);
    printf("After reverse: ");
    DListPrint(L);
    DListReverse(L);
    Check(L, deleted, 4);
    REQUIRE(DListDeleteValue(L, 30) == DLIST_OK);
    REQUIRE(DListDeleteValue(L, 99) == DLIST_ERR);
    ElemType remaining[] = {10, 15, 40};
    Check(L, remaining, 3);
    ElemType repeated[] = {2, 2, 1, 2, 3, 2};
    REQUIRE(DListAssign(L, repeated, 6) == DLIST_OK);
    REQUIRE(DListLocateElem(L, 2) == 1);
    REQUIRE(DListNextElem(L, 2, &x) == DLIST_OK && x == 2);
    REQUIRE(DListDeleteValue(L, 2) == DLIST_OK);
    REQUIRE(DListRemoveAll(L, 2) == 3);
    ElemType kept[] = {1, 3};
    Check(L, kept, 2);
    REQUIRE(DListRemoveAll(L, 99) == 0);
    REQUIRE(DListRemoveAll(L, 1) == 1 && DListRemoveAll(L, 3) == 1);
    Check(L, NULL, 0);
    REQUIRE(DListPushBack(L, 8) == DLIST_OK);
    REQUIRE(DListPopBack(L, NULL) == DLIST_OK);
    Check(L, NULL, 0);
    REQUIRE(DListPushFront(L, 8) == DLIST_OK);
    DListReverse(L);
    REQUIRE(DListPopFront(L, &x) == DLIST_OK && x == 8);
    Check(L, NULL, 0);

    REQUIRE(DListInsertOrdered(L, 20) == DLIST_OK);
    REQUIRE(DListInsertOrdered(L, 10) == DLIST_OK);
    REQUIRE(DListInsertOrdered(L, 30) == DLIST_OK);
    DListNode *originalTwenty = DListGetNode(L, 2);
    REQUIRE(DListInsertOrdered(L, 20) == DLIST_OK);
    REQUIRE(DListGetNode(L, 2) == originalTwenty);
    ElemType ordered[] = {10, 20, 20, 30};
    Check(L, ordered, 4);
    printf("Ordered insert: ");
    DListPrint(L);

    DLinkList A = NULL, B = NULL, C = NULL;
    REQUIRE(DListInit(&A) == DLIST_OK && DListInit(&B) == DLIST_OK);
    REQUIRE(DListInit(&C) == DLIST_OK);
    ElemType left[] = {1, 2};
    ElemType right[] = {3, 4};
    REQUIRE(DListAssign(A, left, 2) == DLIST_OK);
    REQUIRE(DListAssign(B, right, 2) == DLIST_OK);
    DListNode *rightFirst = B->next;
    REQUIRE(DListConcat(A, A) == DLIST_ERR);
    REQUIRE(DListConcat(NULL, B) == DLIST_ERR);
    REQUIRE(DListConcat(A, B) == DLIST_OK);
    ElemType joined[] = {1, 2, 3, 4};
    Check(A, joined, 4);
    Check(B, NULL, 0);
    REQUIRE(DListGetNode(A, 3) == rightFirst);
    REQUIRE(DListConcat(A, B) == DLIST_OK);
    REQUIRE(DListConcat(C, A) == DLIST_OK);
    Check(C, joined, 4);
    Check(A, NULL, 0);
    DListClear(C);

    ElemType av[] = {1, 3, 3, 7};
    ElemType bv[] = {2, 3, 8};
    REQUIRE(DListAssign(A, av, 4) == DLIST_OK);
    REQUIRE(DListAssign(B, bv, 3) == DLIST_OK);
    REQUIRE(DListMergeSorted(A, A, B) == DLIST_ERR);
    REQUIRE(DListMergeSorted(C, A, A) == DLIST_ERR);
    REQUIRE(DListMergeSorted(NULL, A, B) == DLIST_ERR);
    DListNode *aThree = A->next->next;
    DListNode *aNextThree = aThree->next;
    DListNode *bThree = B->next->next;
#ifdef DLIST_TEST_ALLOCATOR
    oldLive = liveNodes;
    failAfter = 0;
#endif
    REQUIRE(DListMergeSorted(C, A, B) == DLIST_OK);
#ifdef DLIST_TEST_ALLOCATOR
    REQUIRE(failAfter == 0 && liveNodes == oldLive);
    failAfter = -1;
#endif
    ElemType merged[] = {1, 2, 3, 3, 3, 7, 8};
    Check(C, merged, 7);
    Check(A, NULL, 0);
    Check(B, NULL, 0);
    REQUIRE(DListGetNode(C, 3) == aThree && aThree->next == aNextThree);
    REQUIRE(aNextThree->next == bThree);
    printf("After merge: ");
    DListPrint(C);
    REQUIRE(DListMergeSorted(C, A, B) == DLIST_ERR);
    Check(C, merged, 7);
    DListClear(C);
    ElemType unsorted[] = {3, 1};
    REQUIRE(DListAssign(A, unsorted, 2) == DLIST_OK);
    REQUIRE(DListAssign(B, bv, 3) == DLIST_OK);
    REQUIRE(DListMergeSorted(C, A, B) == DLIST_ERR);
    Check(A, unsorted, 2);
    Check(B, bv, 3);
    Check(C, NULL, 0);
    DListClear(A);
    REQUIRE(DListMergeSorted(C, A, B) == DLIST_OK);
    Check(C, bv, 3);
    Check(B, NULL, 0);
    DListClear(C);
    REQUIRE(DListMergeSorted(C, A, B) == DLIST_OK);
    Check(C, NULL, 0);
    DListDestroy(&A);
    DListDestroy(&B);
    DListDestroy(&C);

    ModelChecks(L);
    DListClear(L);
    REQUIRE(L == head);
    Check(L, NULL, 0);
    REQUIRE(DListAssign(L, NULL, 0) == DLIST_OK);
    DListDestroy(&L);
    REQUIRE(L == NULL);
    DListDestroy(&L);
    DListDestroy(NULL);
    DListClear(NULL);
    DListReverse(NULL);
    REQUIRE(DListInit(&L) == DLIST_OK);
    DListDestroy(&L);
#ifdef DLIST_TEST_ALLOCATOR
    REQUIRE(liveNodes == 0);
    puts("Allocation failure and allocation/free balance checks passed.");
#endif
    puts("All DList checks passed.");
    return 0;
}

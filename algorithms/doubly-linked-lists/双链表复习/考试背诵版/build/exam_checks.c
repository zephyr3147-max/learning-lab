/* 独立验证考试简版，不属于需要背诵的内容。 */
#include <stdio.h>
#include <stdlib.h>

static int failNext = 0;
static int liveNodes = 0;

static void *ExamMalloc(size_t size)
{
    if (failNext)
    {
        failNext = 0;
        return NULL;
    }
    void *p = malloc(size);
    if (p != NULL)
    {
        ++liveNodes;
    }
    return p;
}

static void ExamFree(void *p)
{
    if (p != NULL)
    {
        --liveNodes;
    }
    free(p);
}

#define malloc ExamMalloc
#define free ExamFree
#define main ExamDemoMain
#include "../双链表_考试最小背诵版.c"
#undef main
#undef free
#undef malloc

static void Require(int ok, int line)
{
    if (!ok)
    {
        fprintf(stderr, "Exam check failed at line %d\n", line);
        exit(1);
    }
}
#define CHECK(expr) Require((expr), __LINE__)

static void Check(DLinkList L, const int a[], int n)
{
    CHECK(L != NULL);
    CHECK(L->next->prev == L);
    CHECK(L->prev->next == L);
    Node *p = L->next;
    for (int i = 0; i < n; ++i)
    {
        CHECK(p != L);
        CHECK(p->data == a[i]);
        CHECK(p->next->prev == p);
        CHECK(p->prev->next == p);
        p = p->next;
    }
    CHECK(p == L);
    p = L->prev;
    for (int i = n - 1; i >= 0; --i)
    {
        CHECK(p != L);
        CHECK(p->data == a[i]);
        p = p->prev;
    }
    CHECK(p == L);
}

int main(void)
{
    DLinkList L = NULL;
    CHECK(InitList(NULL) == 0);
    failNext = 1;
    CHECK(InitList(&L) == 0 && L == NULL && liveNodes == 0);
    CHECK(InitList(&L) == 1);
    CHECK(InitList(&L) == 0);
    Check(L, NULL, 0);

    int e = -1;
    CHECK(GetElem(L, 1, &e) == 0 && e == -1);
    CHECK(ListDelete(L, 1, &e) == 0 && e == -1);
    CHECK(ListInsert(L, 0, 9) == 0);
    CHECK(ListInsert(L, 2, 9) == 0);
    failNext = 1;
    CHECK(ListInsert(L, 1, 9) == 0 && liveNodes == 1);
    Check(L, NULL, 0);

    CHECK(ListInsert(L, 1, 10) == 1);
    CHECK(ListInsert(L, 2, 30) == 1);
    CHECK(ListInsert(L, 2, 20) == 1);
    const int a[] = {10, 20, 30};
    Check(L, a, 3);
    CHECK(GetElem(L, 2, &e) == 1 && e == 20);
    CHECK(GetElem(L, 0, &e) == 0 && e == 20);
    CHECK(GetElem(L, 4, &e) == 0 && e == 20);
    CHECK(GetElem(L, 1, NULL) == 0);
    CHECK(LocateElem(L, 20) == 2);
    CHECK(LocateElem(L, 99) == 0);
    CHECK(ListInsert(L, 5, 9) == 0);
    failNext = 1;
    CHECK(ListInsert(L, 2, 9) == 0 && liveNodes == 4);
    Check(L, a, 3);

    CHECK(ListDelete(L, 2, &e) == 1 && e == 20);
    const int b[] = {10, 30};
    Check(L, b, 2);
    CHECK(ListDelete(L, 1, NULL) == 1);
    const int c[] = {30};
    Check(L, c, 1);
    CHECK(ListDelete(L, 1, &e) == 1 && e == 30);
    Check(L, NULL, 0);
    CHECK(ListInsert(L, 1, 7) == 1);
    CHECK(ListInsert(L, 2, 7) == 1);
    CHECK(LocateElem(L, 7) == 1);

    DestroyList(&L);
    CHECK(L == NULL && liveNodes == 0);
    DestroyList(&L);
    DestroyList(NULL);
    CHECK(GetElem(NULL, 1, &e) == 0);
    CHECK(ListInsert(NULL, 1, 7) == 0);
    CHECK(ListDelete(NULL, 1, &e) == 0);
    puts("Exam version: boundary, bidirectional-link, allocation-failure and free-balance checks passed.");
    return 0;
}


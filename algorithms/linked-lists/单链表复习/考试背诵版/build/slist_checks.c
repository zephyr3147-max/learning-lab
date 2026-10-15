/* 验证用代码，不属于考试背诵内容。 */
#include <stdlib.h>

static int failNextAllocation = 0;
static void *ExamMalloc(size_t bytes)
{
    if (failNextAllocation)
    {
        failNextAllocation = 0;
        return NULL;
    }
    return malloc(bytes);
}

#define malloc ExamMalloc
#define main SListDemoMain
#include "../单链表_考试最小背诵版.c"
#undef main
#undef malloc

#define CHECK(condition) do { if (!(condition)) { fprintf(stderr, "Check failed at line %d\n", __LINE__); return 1; } } while (0)

int main(void)
{
    LinkList L = NULL;
    ElemType e = -1;
    CHECK(InitList(NULL) == 0);
    failNextAllocation = 1;
    CHECK(InitList(&L) == 0 && L == NULL);
    CHECK(InitList(&L) == 1 && L->next == NULL);
    Node *head = L;
    CHECK(InitList(&L) == 0 && L == head);
    CHECK(GetElem(NULL, 1, &e) == 0 && e == -1);
    CHECK(LocateElem(NULL, 10) == 0);
    CHECK(ListInsert(NULL, 1, 10) == 0);
    CHECK(ListDelete(NULL, 1, &e) == 0 && e == -1);
    CHECK(GetElem(L, 1, &e) == 0 && e == -1);
    CHECK(GetElem(L, 0, &e) == 0 && e == -1);
    CHECK(ListDelete(L, 1, &e) == 0 && e == -1);
    CHECK(ListInsert(L, 0, 10) == 0);
    CHECK(ListInsert(L, 2, 10) == 0);
    CHECK(LocateElem(L, 10) == 0);

    failNextAllocation = 1;
    CHECK(ListInsert(L, 1, 10) == 0 && L->next == NULL);
    CHECK(ListInsert(L, 1, 10) == 1);
    CHECK(ListInsert(L, 2, 30) == 1);
    CHECK(ListInsert(L, 2, 20) == 1);
    int expected[] = {10, 20, 30};
    for (int i = 1; i <= 3; ++i)
    {
        CHECK(GetElem(L, i, &e) == 1 && e == expected[i - 1]);
        CHECK(LocateElem(L, expected[i - 1]) == i);
    }
    e = -1;
    CHECK(GetElem(L, 4, &e) == 0 && e == -1);
    CHECK(GetElem(L, 1, NULL) == 0);
    CHECK(ListInsert(L, 5, 99) == 0);
    CHECK(ListDelete(L, 4, &e) == 0 && e == -1);

    Node *first = L->next;
    Node *second = first->next;
    failNextAllocation = 1;
    CHECK(ListInsert(L, 2, 99) == 0);
    CHECK(L->next == first && first->next == second);
    for (int i = 1; i <= 3; ++i)
    {
        CHECK(GetElem(L, i, &e) == 1 && e == expected[i - 1]);
    }
    CHECK(ListInsert(L, 4, 20) == 1);
    CHECK(LocateElem(L, 20) == 2);
    CHECK(ListDelete(L, 1, &e) == 1 && e == 10);
    CHECK(ListDelete(L, 2, &e) == 1 && e == 30);
    CHECK(ListDelete(L, 2, NULL) == 1);
    CHECK(GetElem(L, 1, &e) == 1 && e == 20);
    CHECK(ListDelete(L, 1, &e) == 1 && e == 20);
    CHECK(L->next == NULL);
    e = -1;
    CHECK(ListDelete(L, 1, &e) == 0 && e == -1);
    DestroyList(&L);
    CHECK(L == NULL);
    DestroyList(&L);
    DestroyList(NULL);

    CHECK(InitList(&L) == 1);
    for (int i = 0; i < 2000; ++i)
    {
        CHECK(ListInsert(L, 1, i) == 1);
    }
    CHECK(GetElem(L, 2000, &e) == 1 && e == 0);
    CHECK(GetElem(L, 1, &e) == 1 && e == 1999);
    CHECK(ListDelete(L, 2000, &e) == 1 && e == 0);
    DestroyList(&L);
    CHECK(L == NULL);
    CHECK(InitList(&L) == 1 && L->next == NULL);
    DestroyList(&L);
    puts("All SList boundary and allocation-failure checks passed.");
    return 0;
}

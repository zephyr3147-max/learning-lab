/* 独立验证用，不属于需要背诵的代码。 */
#define main SqListDemoMain
#include "../顺序表_考试最小背诵版.c"
#undef main

#define CHECK(condition) do { if (!(condition)) return __LINE__; } while (0)

int main(void)
{
    SqList L;
    ElemType e = -1;
    InitList(&L);
    CHECK(L.length == 0);
    CHECK(!GetElem(&L, 1, &e) && e == -1);
    CHECK(!ListDelete(&L, 1, &e) && e == -1);
    CHECK(!ListInsert(&L, 0, 10));
    CHECK(!ListInsert(&L, 2, 10));
    CHECK(LocateElem(&L, 10) == 0);

    for (int j = 0; j < MAXSIZE; ++j)
        CHECK(ListInsert(&L, L.length + 1, j));
    CHECK(L.length == MAXSIZE);
    CHECK(!ListInsert(&L, 1, 999));
    CHECK(!ListInsert(&L, L.length + 1, 999));
    CHECK(!ListInsert(&L, L.length + 2, 999));
    CHECK(!ListDelete(&L, 0, &e) && e == -1);
    CHECK(!ListDelete(&L, L.length + 1, &e) && e == -1);
    CHECK(!GetElem(&L, 0, &e) && e == -1);
    CHECK(!GetElem(&L, L.length + 1, &e) && e == -1);
    CHECK(!GetElem(&L, 1, NULL));
    for (int j = 0; j < MAXSIZE; ++j)
    {
        CHECK(GetElem(&L, j + 1, &e) && e == j);
        CHECK(LocateElem(&L, j) == j + 1);
    }

    CHECK(ListDelete(&L, 1, &e) && e == 0);
    CHECK(ListInsert(&L, 1, 999));
    CHECK(L.length == MAXSIZE && L.data[0] == 999);
    for (int j = 1; j < MAXSIZE; ++j)
        CHECK(L.data[j] == j);
    CHECK(ListDelete(&L, L.length, &e) && e == MAXSIZE - 1);
    CHECK(ListInsert(&L, 2, 888));
    CHECK(L.data[0] == 999 && L.data[1] == 888 && L.data[2] == 1);
    CHECK(ListDelete(&L, 2, NULL));
    CHECK(L.data[1] == 1 && L.length == MAXSIZE - 1);

    InitList(&L);
    CHECK(ListInsert(&L, 1, 7) && ListInsert(&L, 2, 7));
    CHECK(LocateElem(&L, 7) == 1 && LocateElem(&L, 8) == 0);
    while (L.length > 0)
        CHECK(ListDelete(&L, 1, &e));
    CHECK(L.length == 0 && !ListDelete(&L, 1, &e));
    puts("All exam-version boundary checks passed.");
    return 0;
}

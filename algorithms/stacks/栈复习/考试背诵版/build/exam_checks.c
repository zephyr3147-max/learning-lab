/* 额外验证，不属于考试需要背诵的内容。 */
#include <stdio.h>
#include <stdlib.h>
#define main ExamDemoMain
#include "../栈_考试最小背诵版.c"
#undef main

static void Require(int ok, int line)
{
    if (!ok)
    {
        fprintf(stderr, "Exam check failed at line %d\n", line);
        exit(1);
    }
}
#define CHECK(x) Require((x), __LINE__)

int main(void)
{
    SqStack S;
    InitStack(&S);
    int e = -999;
    CHECK(StackEmpty(&S) && StackLength(&S) == 0);
    CHECK(!GetTop(&S, &e) && e == -999);
    CHECK(!Pop(&S, &e) && e == -999);
    for (int i = 0; i < MAXSIZE; ++i)
    {
        CHECK(Push(&S, i));
    }
    CHECK(StackLength(&S) == MAXSIZE);
    CHECK(!Push(&S, 999) && StackLength(&S) == MAXSIZE);
    CHECK(GetTop(&S, &e) && e == MAXSIZE - 1);
    CHECK(!GetTop(&S, NULL));
    for (int i = MAXSIZE - 1; i >= 0; --i)
    {
        CHECK(Pop(&S, &e) && e == i);
    }
    CHECK(StackEmpty(&S));
    CHECK(Push(&S, 42) && Pop(&S, NULL) && StackEmpty(&S));
    CHECK(Push(&S, 43));
    ClearStack(&S);
    CHECK(StackEmpty(&S) && Push(&S, 44));
    puts("Exam stack: full/empty, LIFO, output and reuse checks passed.");
    return 0;
}


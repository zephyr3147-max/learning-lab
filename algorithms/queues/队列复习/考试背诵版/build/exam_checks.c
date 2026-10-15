/* 额外验证，不属于考试需要背诵的内容。 */
#include <stdio.h>
#include <stdlib.h>
#define main ExamDemoMain
#include "../队列_考试最小背诵版.c"
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
    SqQueue Q;
    InitQueue(&Q);
    int e = -999;
    CHECK(QueueEmpty(&Q) && !QueueFull(&Q) && QueueLength(&Q) == 0);
    CHECK(!GetHead(&Q, &e) && e == -999);
    CHECK(!DeQueue(&Q, &e) && e == -999);
    for (int i = 0; i < MAXSIZE - 1; ++i)
    {
        CHECK(EnQueue(&Q, i));
    }
    CHECK(QueueFull(&Q) && QueueLength(&Q) == MAXSIZE - 1);
    CHECK(!EnQueue(&Q, 999) && QueueLength(&Q) == MAXSIZE - 1);
    CHECK(GetHead(&Q, &e) && e == 0);
    CHECK(!GetHead(&Q, NULL));
    for (int i = 0; i < 50; ++i)
    {
        CHECK(DeQueue(&Q, &e) && e == i);
    }
    for (int i = MAXSIZE - 1; i < MAXSIZE - 1 + 50; ++i)
    {
        CHECK(EnQueue(&Q, i));
    }
    CHECK(Q.rear < Q.front && QueueFull(&Q));
    for (int i = 50; i < MAXSIZE - 1 + 50; ++i)
    {
        CHECK(DeQueue(&Q, &e) && e == i);
    }
    CHECK(QueueEmpty(&Q));
    for (int i = 0; i < 1000; ++i)
    {
        CHECK(EnQueue(&Q, i) && GetHead(&Q, &e) && e == i);
        CHECK(DeQueue(&Q, &e) && e == i && QueueEmpty(&Q));
    }
    CHECK(EnQueue(&Q, 42) && DeQueue(&Q, NULL) && QueueEmpty(&Q));
    CHECK(EnQueue(&Q, 43));
    ClearQueue(&Q);
    CHECK(Q.front == 0 && Q.rear == 0 && QueueEmpty(&Q));
    puts("Exam queue: full/empty, wraparound, FIFO and reuse checks passed.");
    return 0;
}


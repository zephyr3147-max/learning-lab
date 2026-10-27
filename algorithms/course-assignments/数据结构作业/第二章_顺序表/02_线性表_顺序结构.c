#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct SqList
{
    int* data;
    int length;
} SqList;

/* 读入 n 个元素，额外预留一个位置用于本题的一次插入。O(n)。 */
void ReadList(SqList* L, int n)
{
    L->data = (int*)malloc((n + 1) * sizeof(int));
    if (L->data == NULL)
    {
        exit(1);
    }
    L->length = n;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &L->data[i]);
    }
}

/* 插入成功返回 1，位置越界返回 0。O(n)。 */
int Insert(SqList* L, int pos, int value)
{
    if (pos < 1 || pos > L->length + 1)
    {
        return 0;
    }
    /* 从后往前移动，避免覆盖原数据。 */
    for (int i = L->length; i >= pos; --i)
    {
        L->data[i] = L->data[i - 1];
    }
    L->data[pos - 1] = value;
    ++L->length;
    return 1;
}

/* 输出顺序表，元素间一个空格。O(n)。 */
void PrintList(const SqList* L)
{
    for (int i = 0; i < L->length; ++i)
    {
        printf("%d", L->data[i]);
        if (i + 1 < L->length)
        {
            printf(" ");
        }
    }
    printf("\n");
}

int main(void)
{
    SqList L;
    int n;
    int pos;
    int value;
    scanf("%d", &n);
    ReadList(&L, n);
    scanf("%d%d", &pos, &value);
    if (Insert(&L, pos, value) == 1)
    {
        PrintList(&L);
    }
    free(L.data);
    return 0;
}

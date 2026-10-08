#include <stdio.h>

#define MAXSIZE 100
typedef int ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int length;
} SqList;

/* 初始化：把顺序表设为空表，只将 length 置为 0，不清零数组。
 * 参数 L：待初始化的表地址；无返回值。O(1)。
 */
void InitList(SqList *L)
{
    L->length = 0;
}

/* 按位取值：读取第 i 个元素，不改变原表。
 * 参数 L：表地址；i：位置（1..length）；e：接收结果的变量地址。
 * 返回 1 表示成功，0 表示失败；失败不修改 *e。O(1)。
 */
int GetElem(const SqList *L, int i, ElemType *e)
{
    if (i < 1 || i > L->length || e == NULL)
        return 0;
    *e = L->data[i - 1];
    return 1;
}

/* 按值查找：从头查找第一个值等于 e 的元素，不改变原表。
 * 参数 L：表地址；e：要查找的值。
 * 返回从 1 开始的位置，找不到返回 0。最坏 O(n)。
 */
int LocateElem(const SqList *L, ElemType e)
{
    for (int j = 0; j < L->length; ++j)
        if (L->data[j] == e)
            return j + 1;
    return 0;
}

/* 插入：将 e 插到第 i 个位置，后续元素右移，表长加 1。
 * 参数 L：表地址；i：位置（1..length+1）；e：要插入的值。
 * 返回 1 表示成功；位置非法或表满返回 0，原表不变。最坏 O(n)。
 */
int ListInsert(SqList *L, int i, ElemType e)
{
    if (i < 1 || i > L->length + 1 || L->length == MAXSIZE)
        return 0;
    for (int j = L->length; j >= i; --j)
        L->data[j] = L->data[j - 1];
    L->data[i - 1] = e;
    ++L->length;
    return 1;
}

/* 删除：删除第 i 个元素，后续元素左移，表长减 1。
 * 参数 L：表地址；i：位置（1..length）；e：接收被删值的变量地址，
 * 可传 NULL 表示不接收。返回 1 表示成功；位置非法返回 0，
 * 原表和输出值不变。最坏 O(n)。
 */
int ListDelete(SqList *L, int i, ElemType *e)
{
    if (i < 1 || i > L->length)
        return 0;
    if (e != NULL)
        *e = L->data[i - 1];
    for (int j = i; j < L->length; ++j)
        L->data[j - 1] = L->data[j];
    --L->length;
    return 1;
}

/* 遍历输出：依次打印有效元素，以空格分隔，最后换行；空表只换行。
 * 参数 L：表地址；不改变原表，无返回值。O(n)。
 */
void PrintList(const SqList *L)
{
    for (int j = 0; j < L->length; ++j)
        printf("%d ", L->data[j]);
    printf("\n");
}

/* main 是调用示例；考试只写题目要求的部分。 */
int main(void)
{
    SqList L;
    ElemType e;
    InitList(&L);
    if (!ListInsert(&L, 1, 10) || !ListInsert(&L, 2, 30)
        || !ListInsert(&L, 2, 20))
        return 1;
    PrintList(&L);
    if (!ListDelete(&L, 2, &e))
        return 1;
    printf("deleted: %d\n", e);
    PrintList(&L);
    if (!GetElem(&L, 2, &e))
        return 1;
    printf("second: %d\n", e);
    printf("position of 30: %d\n", LocateElem(&L, 30));
    return 0;
}

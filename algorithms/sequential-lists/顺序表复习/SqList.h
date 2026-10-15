#pragma once

#include <stddef.h> /* NULL */

#define SQLIST_INIT_CAPACITY 100
#define SQLIST_OK 1
#define SQLIST_ERR 0

typedef int ElemType;

typedef struct SqList
{
    ElemType *data; /* 动态数组，用 realloc 扩容，用 free 释放 */
    int length; /* 有效元素个数，不是数组容量 */
    int capacity; /* 当前分配的元素格数，不是字节数 */
} SqList;

/* 使用约定：
 * 1. 先声明 SqList L = {0}，检查 Init 成功后再使用其他接口。
 * 2. 0 <= length <= capacity，不要直接改 length/capacity/data。
 * 3. 接口位置从 1 开始；数组下标从 0 开始。
 * 4. 取/改/删位置为 1..length；插入位置为 1..length+1。
 * 5. OK/ERR 表示操作成功/失败；Empty/Full 返回判断结果 1/0。
 * 6. 输出参数指向表外有效的 ElemType 变量，不得指向本表字段。
 * 7. 不要直接用 L2 = L 复制动态表：会共享指针，导致重复释放。
 * 8. 扩容可能更换 data 地址，保存过的元素地址必须重新取得。
 * 9. Destroy 后可以再次 Init；Clear 保留容量和数组，可以直接复用。
 */

/* ① 初始化、判空、判满、求长度：O(1) */
int SqListInit(SqList *L); /* 分配初始数组；失败返回 ERR，不能重复初始化活表 */
int SqListEmpty(const SqList *L);
int SqListFull(const SqList *L);
int SqListLength(const SqList *L);
int SqListCapacity(const SqList *L);
/* 至少提供 minCapacity 个格子，按需倍增；失败不改原表。
 * 只扩容、不缩容，预留容量不会改变 length。
 * 已有容量足够为 O(1)，实际扩容最坏 O(capacity)。
 */
int SqListReserve(SqList *L, int minCapacity);

/* ② 遍历：O(n)；空表只输出换行 */
void SqListPrint(const SqList *L);

/* ③ 按位取值/修改：O(1)；失败不修改输出值或原表 */
int SqListGetElem(const SqList *L, int i, ElemType *outValue);
int SqListSetElem(SqList *L, int i, ElemType value);

/* ④ 按值查找：O(n)；返回第一个匹配位置，找不到返回 0 */
int SqListLocateElem(const SqList *L, ElemType value);
/* 找第一个匹配元素的前驱/后继，O(n)；不存在返回 ERR */
int SqListPriorElem(const SqList *L, ElemType value, ElemType *outValue);
int SqListNextElem(const SqList *L, ElemType value, ElemType *outValue);

/* ⑤ 插入：最坏 O(n)，连续尾插均摊 O(1)。空间不足时自动扩容。
 * 位置非法、容量超过可表示范围或分配失败时不改原表。
 */
int SqListInsert(SqList *L, int i, ElemType value);
int SqListPushBack(SqList *L, ElemType value);

/* ⑥ 删除：最坏 O(n)，尾删 O(1)
 * outValue 可以为 NULL，表示不需要取回被删值；失败不改输出值。
 */
int SqListDelete(SqList *L, int i, ElemType *outValue);
int SqListPopBack(SqList *L, ElemType *outValue);

/* ⑦ 批量赋值：O(n)，数组 a 至少包含 n 个有效元素。
 * n 为 0 时允许 a == NULL；n 为负或 a 非法时原表不变。
 * 空间不足时自动扩容；a 必须指向独立数组，不能引用 L->data 内部。
 */
int SqListAssign(SqList *L, const ElemType a[], int n);

/* ⑧ Clear 保留动态数组，仅重置 length。
 * Destroy 释放数组，data=NULL、length=capacity=0，可重复调用。
 * Destroy 不释放 SqList 结构体变量自身。
 */
void SqListClear(SqList *L);
void SqListDestroy(SqList *L);

/* ⑨ 逆序和批量删除：O(n) 时间、O(1) 辅助空间 */
void SqListReverse(SqList *L);
int SqListRemoveAll(SqList *L, ElemType value); /* 返回删除的元素数 */
/* 有序插入：最坏 O(n)，扩容可能需要 O(n) 额外空间。
 * 前提：原表非递减有序；插到同值元素之后，不自动排序或检查有序性。
 */
int SqListInsertOrdered(SqList *L, ElemType value);


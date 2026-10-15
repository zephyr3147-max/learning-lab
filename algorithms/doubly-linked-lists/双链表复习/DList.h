#pragma once
#include <stddef.h>

#define DLIST_OK 1
#define DLIST_ERR 0
typedef int ElemType;

typedef struct DListNode
{
    ElemType data;
    struct DListNode *prev;
    struct DListNode *next;
} DListNode;
typedef DListNode *DLinkList;

/* 带头、循环、整数双链表。数据结点数量须可用 int 表示。
 * 先声明 DLinkList L=NULL，检查 Init(&L) 成功后使用。
 * 头结点不算元素；插入位置 1..n+1，取值/修改/删除位置 1..n。
 * 输出参数指向表外有效变量，不能指向待删除结点内部。
 * 不复制头指针当独立副本，不让不同链表共享结点。
 * 地址型接口的指针必须有效、未释放且满足归属前提。
 */

/* ① 初始化：申请头结点，双向指回自身。O(1)。失败不改原指针。 */
int DListInit(DLinkList *L);
/* 判空：已初始化表 next 指回自身；NULL 返回 0。O(1)。 */
int DListEmpty(const DListNode *L);
/* 求长：遍历计数，不计头结点。O(n)。NULL 返回 0。 */
int DListLength(const DListNode *L);
/* 正向输出：遇头结点停止，不输出头结点。O(n)。 */
void DListPrint(const DListNode *L);
/* 反向输出：从 prev 出发，不改原表。O(n)。 */
void DListPrintReverse(const DListNode *L);

/* ② 返回第 i 个数据结点地址，非法返回 NULL，不交出头结点。O(n)。 */
DListNode *DListGetNode(DLinkList L, int i);
/* 按位取值：成功写 outValue，失败不修改输出。O(n)。 */
int DListGetElem(const DListNode *L, int i, ElemType *outValue);
/* 按位修改：只改 data，不改链接。O(n)。 */
int DListSetElem(DLinkList L, int i, ElemType value);
/* 查找第一个匹配位置，找不到返回 0。O(n)。 */
int DListLocateElem(const DListNode *L, ElemType value);
/* 第一个匹配的数据前驱值，首元素/未找到失败。O(n)。 */
int DListPriorElem(const DListNode *L, ElemType value, ElemType *outValue);
/* 第一个匹配的数据后继值，尾元素/未找到失败。O(n)。 */
int DListNextElem(const DListNode *L, ElemType value, ElemType *outValue);

/* ③ 已知 position，在其前插入。position 必须是有效成员，可为头结点。
 * O(1)，参数 NULL 或分配失败返回 ERR，不改原表。
 */
int DListInsertBefore(DListNode *position, ElemType value);
/* 按位插入：允许 1..n+1，非法/分配失败不改原表。O(n)。 */
int DListInsert(DLinkList L, int i, ElemType value);
/* 直接在首结点前插入，空表也适用。O(1)。 */
int DListPushFront(DLinkList L, ElemType value);
/* 直接在头结点前插入，即尾插。O(1)。 */
int DListPushBack(DLinkList L, ElemType value);

/* ④ 已知 node 删除：O(1)。node 必须属于 L 且不是头结点。
 * 只检查 NULL/头结点，不遍历验证归属；外来或失效指针属错误用法。
 * outValue 可为 NULL；失败不修改输出。
 */
int DListErase(DLinkList L, DListNode *node, ElemType *outValue);
/* 按位删除：先定位，再断链释放。O(n)。 */
int DListDelete(DLinkList L, int i, ElemType *outValue);
/* 直接删除首/尾数据结点，空表失败。O(1)。 */
int DListPopFront(DLinkList L, ElemType *outValue);
int DListPopBack(DLinkList L, ElemType *outValue);
/* 删除第一个等于 value 的数据结点，未找到返回 ERR。O(n)。 */
int DListDeleteValue(DLinkList L, ElemType value);
/* 删除全部匹配结点，返回删除数量。O(n)。 */
int DListRemoveAll(DLinkList L, ElemType value);

/* ⑤ 从外部数组替换建表，保持数组顺序。旧表 m 个、新表 n 个：O(m+n)。
 * n>=0；n=0 允许 a=NULL。临时建表 O(n) 存储；失败保留旧表并回收临时链。
 */
int DListAssign(DLinkList L, const ElemType a[], int n);
/* 清空：只释放数据结点，保留头结点，双向指回自身。O(n)。 */
void DListClear(DLinkList L);
/* 销毁：连头结点一起释放，外部 L=NULL，可重复调用。O(n)。 */
void DListDestroy(DLinkList *L);

/* ⑥ 逆置：交换每个结点（包括头）的 prev/next，不申请新结点。O(n)。 */
void DListReverse(DLinkList L);
/* 倒数第 k 个：直接从尾部向前走。有效时 O(k)，最坏 O(n)。 */
int DListGetFromBack(const DListNode *L, int k, ElemType *outValue);
/* 有序插入：前提原表非递减，插在同值结点之后；不自动排序/检查。O(n)。 */
int DListInsertOrdered(DLinkList L, ElemType value);
/* 将 src 全部数据结点拼到 dest 尾部，保留两个头结点，src 变空。O(1)。
 * 两张表必须独立；NULL/同一头指针失败。无分配，转移结点所有权。
 */
int DListConcat(DLinkList dest, DLinkList src);
/* 两张非递减表稳定合并到空 dest，三张表必须独立。O(m+n)，辅助空间 O(1)。
 * 检查有序性；失败不改三张表。成功后 a/b 变空，数据结点归 dest。
 */
int DListMergeSorted(DLinkList dest, DLinkList a, DLinkList b);

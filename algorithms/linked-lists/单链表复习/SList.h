#pragma once

#include <stddef.h> /* NULL、size_t */

#define SLIST_OK 1
#define SLIST_ERR 0
typedef int ElemType;

typedef struct SListNode
{
    ElemType data;
    struct SListNode *next;
} SListNode;
typedef SListNode *LinkList;

/* 约定：
 * 1. 带头结点、非循环；头结点不属于数据元素。总元素数须可用 int 表示。
 * 2. 先声明 LinkList L = NULL，检查 SListInit(&L) 成功后使用。
 * 3. 插入位置为 1..n+1，取值/修改/删除位置为 1..n。
 * 4. 输出参数指向链表外有效的 ElemType 变量，不得指向被删除的结点。
 * 5. 不复制头指针作为独立副本，不手动形成环，不让两个表共享结点。
 * 6. Init/Destroy 用 &L；其他接口使用 L，即头结点地址。
 * 7. OK/ERR 为状态；Locate 返回位置或 0；RemoveAll 返回删除数量。
 */

/* ① 初始化：创建头结点。O(1)。拒绝重复初始化；失败不改原指针。 */
int SListInit(LinkList *L);
/* 判空：初始化后的 L->next 为 NULL 才为空表。O(1)。NULL 返回 0。 */
int SListEmpty(const SListNode *L);
/* 求长：统计数据结点，不计头结点。O(n)。NULL 返回 0。 */
int SListLength(const SListNode *L);
/* 遍历：打印有效元素，空表输出换行，NULL 不输出。O(n)。 */
void SListPrint(const SListNode *L);

/* ② 取值：第 i 个元素写入 outValue；失败不修改输出。最坏 O(n)。 */
int SListGetElem(const SListNode *L, int i, ElemType *outValue);
/* 修改：替换第 i 个元素值，不改变链接；失败不改原表。最坏 O(n)。 */
int SListSetElem(LinkList L, int i, ElemType value);

/* ③ 查找：返回第一个匹配位置，找不到返回 0。最坏 O(n)。 */
int SListLocateElem(const SListNode *L, ElemType value);
/* 找第一个匹配元素的前驱值，不存在返回 ERR，输出不变。最坏 O(n)。 */
int SListPriorElem(const SListNode *L, ElemType value, ElemType *outValue);
/* 找第一个匹配元素的后继值，不存在返回 ERR，输出不变。最坏 O(n)。 */
int SListNextElem(const SListNode *L, ElemType value, ElemType *outValue);

/* ④ 插入：先定位前驱，再申请结点。位置非法/分配失败不改原表。O(n)。 */
int SListInsert(LinkList L, int i, ElemType value);
/* 头插：在头结点之后插入。O(1)。 */
int SListPushFront(LinkList L, ElemType value);
/* 尾插：本版不缓存尾指针，需寻找末尾。O(n)。 */
int SListPushBack(LinkList L, ElemType value);

/* ⑤ 删除：定位前驱、断链、释放；outValue 可为 NULL。最坏 O(n)。 */
int SListDelete(LinkList L, int i, ElemType *outValue);
/* 头删：删除第一个数据结点，空表失败。O(1)。 */
int SListPopFront(LinkList L, ElemType *outValue);
/* 尾删：定位尾结点前驱，空表失败。O(n)。 */
int SListPopBack(LinkList L, ElemType *outValue);

/* ⑥ 按值删除：只删除第一个匹配结点，找不到返回 ERR。O(n)。 */
int SListDeleteValue(LinkList L, ElemType value);
/* 删除全部匹配结点：返回删除数量，0 也可表示没有匹配。O(n)。 */
int SListRemoveAll(LinkList L, ElemType value);

/* ⑦ 从外部数组替换建表，按输入顺序尾插。旧表 m 个、新表 n 个：O(m+n)。
 * n>=0，a 至少有 n 个元素；n=0 允许 a=NULL。
 * 使用临时链建好后再替换；分配失败保留原表且回收临时结点。
 */
int SListAssign(LinkList L, const ElemType a[], int n);
/* 清空：释放数据结点，保留头结点；可直接复用。O(n)。NULL 无操作。 */
void SListClear(LinkList L);
/* 销毁：连头结点一起释放，外部 L 置 NULL；可重复调用。O(n)。 */
void SListDestroy(LinkList *L);

/* ⑧ 逆置：调整链接，不新建结点，不交换 data。O(n)，辅助空间 O(1)。 */
void SListReverse(LinkList L);
/* 中间元素：快慢指针；偶数长度取靠后的中间元素。O(n)。空表失败。 */
int SListMiddle(const SListNode *L, ElemType *outValue);
/* 倒数第 k 个：双指针相距 k 个结点，k>=1。O(n)。非法时输出不变。 */
int SListKthFromEnd(const SListNode *L, int k, ElemType *outValue);

/* ⑨ 非递减有序表合并：复用原结点，稳定，O(m+n)，辅助空间 O(1)。
 * dest/a/b 为三个独立已初始化的表；dest 必须为空且不与 a/b 相同。
 * 成功后 a/b 变空，数据结点的所有权转移给 dest，各自头结点保留。
 * 本函数检查有序性；参数不符时返回 ERR，不改变三张表。
 */
int SListMergeSorted(LinkList dest, LinkList a, LinkList b);

#include "DList.h"
#include <stdio.h>
#include <stdlib.h>

/* 测试构建模拟申请失败并统计申请/释放；普通构建用标准库。 */
#ifdef DLIST_TEST_ALLOCATOR
void *DListTestMalloc(size_t bytes);
void DListTestFree(void *ptr);
#define DLIST_MALLOC DListTestMalloc
#define DLIST_FREE DListTestFree
#else
#define DLIST_MALLOC malloc
#define DLIST_FREE free
#endif

static DListNode *BuyNode(ElemType value)
{
    DListNode *node = DLIST_MALLOC(sizeof(*node));
    if (node != NULL)
    {
        node->data = value;
        node->next = NULL;
        node->prev = NULL;
    }
    return node;
}

/* allowHead=1 时允许返回第 n+1 个位置的头结点（用于尾插）。 */
static DListNode *FindTarget(const DListNode *L, int i, int allowHead)
{
    if (L == NULL || i < 1)
    {
        return NULL;
    }
    DListNode *p = L->next;
    int j = 1;
    while (p != L && j < i)
    {
        p = p->next;
        ++j;
    }
    if (j != i || (!allowHead && p == L))
    {
        return NULL;
    }
    return p;
}

/* 两边链接操作集中到内部助手。node 已申请，position 有效。 */
static void LinkBefore(DListNode *position, DListNode *node)
{
    node->next = position;
    node->prev = position->prev;
    position->prev->next = node;
    position->prev = node;
}

static void Unlink(DListNode *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

static DListNode *FindValue(const DListNode *L, ElemType value)
{
    if (L == NULL)
    {
        return NULL;
    }
    for (DListNode *p = L->next; p != L; p = p->next)
    {
        if (p->data == value)
        {
            return p;
        }
    }
    return NULL;
}

static int IsSorted(const DListNode *L)
{
    for (const DListNode *p = L->next; p != L && p->next != L; p = p->next)
    {
        if (p->data > p->next->data)
        {
            return 0;
        }
    }
    return 1;
}

/* ① 生命周期、正反向遍历。 */
int DListInit(DLinkList *L)
{
    if (L == NULL || *L != NULL)
    {
        return DLIST_ERR;
    }
    DListNode *head = BuyNode(0);
    if (head == NULL)
    {
        return DLIST_ERR;
    }
    head->next = head;
    head->prev = head;
    *L = head;
    return DLIST_OK;
}

int DListEmpty(const DListNode *L)
{
    return L != NULL && L->next == L;
}

int DListLength(const DListNode *L)
{
    if (L == NULL)
    {
        return 0;
    }
    int n = 0;
    for (const DListNode *p = L->next; p != L; p = p->next)
    {
        ++n;
    }
    return n;
}

void DListPrint(const DListNode *L)
{
    if (L == NULL)
    {
        return;
    }
    for (const DListNode *p = L->next; p != L; p = p->next)
    {
        if (p != L->next)
        {
            printf(" ");
        }
        printf("%d", p->data);
    }
    printf("\n");
}

void DListPrintReverse(const DListNode *L)
{
    if (L == NULL)
    {
        return;
    }
    for (const DListNode *p = L->prev; p != L; p = p->prev)
    {
        if (p != L->prev)
        {
            printf(" ");
        }
        printf("%d", p->data);
    }
    printf("\n");
}

/* ② 按位查询与按值查询。 */
DListNode *DListGetNode(DLinkList L, int i)
{
    return FindTarget(L, i, 0);
}

int DListGetElem(const DListNode *L, int i, ElemType *outValue)
{
    const DListNode *p = FindTarget(L, i, 0);
    if (p == NULL || outValue == NULL)
    {
        return DLIST_ERR;
    }
    *outValue = p->data;
    return DLIST_OK;
}

int DListSetElem(DLinkList L, int i, ElemType value)
{
    DListNode *p = DListGetNode(L, i);
    if (p == NULL)
    {
        return DLIST_ERR;
    }
    p->data = value;
    return DLIST_OK;
}

int DListLocateElem(const DListNode *L, ElemType value)
{
    if (L == NULL)
    {
        return 0;
    }
    int i = 0;
    for (const DListNode *p = L->next; p != L; p = p->next)
    {
        ++i;
        if (p->data == value)
        {
            return i;
        }
    }
    return 0;
}

int DListPriorElem(const DListNode *L, ElemType value, ElemType *outValue)
{
    const DListNode *p = FindValue(L, value);
    if (p == NULL || p->prev == L || outValue == NULL)
    {
        return DLIST_ERR;
    }
    *outValue = p->prev->data;
    return DLIST_OK;
}

int DListNextElem(const DListNode *L, ElemType value, ElemType *outValue)
{
    const DListNode *p = FindValue(L, value);
    if (p == NULL || p->next == L || outValue == NULL)
    {
        return DLIST_ERR;
    }
    *outValue = p->next->data;
    return DLIST_OK;
}

/* ③ 所有插入最终共用四句 LinkBefore。 */
int DListInsertBefore(DListNode *position, ElemType value)
{
    if (position == NULL)
    {
        return DLIST_ERR;
    }
    DListNode *node = BuyNode(value);
    if (node == NULL)
    {
        return DLIST_ERR;
    }
    LinkBefore(position, node);
    return DLIST_OK;
}

int DListInsert(DLinkList L, int i, ElemType value)
{
    return DListInsertBefore(FindTarget(L, i, 1), value);
}

int DListPushFront(DLinkList L, ElemType value)
{
    if (L == NULL)
    {
        return DLIST_ERR;
    }
    return DListInsertBefore(L->next, value);
}

int DListPushBack(DLinkList L, ElemType value)
{
    return DListInsertBefore(L, value);
}

/* ④ 已知结点直接删除，不用重新查前驱。 */
int DListErase(DLinkList L, DListNode *node, ElemType *outValue)
{
    if (L == NULL || node == NULL || node == L)
    {
        return DLIST_ERR;
    }
    if (outValue != NULL)
    {
        *outValue = node->data;
    }
    Unlink(node);
    DLIST_FREE(node);
    return DLIST_OK;
}

int DListDelete(DLinkList L, int i, ElemType *outValue)
{
    return DListErase(L, DListGetNode(L, i), outValue);
}

int DListPopFront(DLinkList L, ElemType *outValue)
{
    if (L == NULL)
    {
        return DLIST_ERR;
    }
    return DListErase(L, L->next, outValue);
}

int DListPopBack(DLinkList L, ElemType *outValue)
{
    if (L == NULL)
    {
        return DLIST_ERR;
    }
    return DListErase(L, L->prev, outValue);
}

int DListDeleteValue(DLinkList L, ElemType value)
{
    return DListErase(L, FindValue(L, value), NULL);
}

int DListRemoveAll(DLinkList L, ElemType value)
{
    if (L == NULL)
    {
        return 0;
    }
    int removed = 0;
    DListNode *p = L->next;
    while (p != L)
    {
        DListNode *next = p->next;
        if (p->data == value)
        {
            DListErase(L, p, NULL);
            ++removed;
        }
        p = next;
    }
    return removed;
}

/* ⑤ 新链建完再替换，失败回收新链、保留旧链。 */
int DListAssign(DLinkList L, const ElemType a[], int n)
{
    if (L == NULL || n < 0 || (n > 0 && a == NULL))
    {
        return DLIST_ERR;
    }
    DListNode dummy = {0, NULL, NULL};
    dummy.next = &dummy;
    dummy.prev = &dummy;
    for (int i = 0; i < n; ++i)
    {
        if (DListPushBack(&dummy, a[i]) != DLIST_OK)
        {
            DListClear(&dummy);
            return DLIST_ERR;
        }
    }
    DListClear(L);
    return DListConcat(L, &dummy);
}

void DListClear(DLinkList L)
{
    if (L == NULL)
    {
        return;
    }
    DListNode *p = L->next;
    while (p != L)
    {
        DListNode *next = p->next;
        DLIST_FREE(p);
        p = next;
    }
    L->next = L;
    L->prev = L;
}

void DListDestroy(DLinkList *L)
{
    if (L == NULL || *L == NULL)
    {
        return;
    }
    DListClear(*L);
    DLIST_FREE(*L);
    *L = NULL;
}

/* ⑥ 原地逆置，头结点也必须交换两条链接。 */
void DListReverse(DLinkList L)
{
    if (L == NULL)
    {
        return;
    }
    DListNode *p = L;
    do
    {
        DListNode *next = p->next;
        p->next = p->prev;
        p->prev = next;
        p = next;
    } while (p != L);
}

int DListGetFromBack(const DListNode *L, int k, ElemType *outValue)
{
    if (L == NULL || k < 1 || outValue == NULL)
    {
        return DLIST_ERR;
    }
    const DListNode *p = L->prev;
    int i = 1;
    while (p != L && i < k)
    {
        p = p->prev;
        ++i;
    }
    if (p == L)
    {
        return DLIST_ERR;
    }
    *outValue = p->data;
    return DLIST_OK;
}

int DListInsertOrdered(DLinkList L, ElemType value)
{
    if (L == NULL)
    {
        return DLIST_ERR;
    }
    DListNode *p = L->next;
    while (p != L && p->data <= value)
    {
        p = p->next;
    }
    return DListInsertBefore(p, value);
}

/* 四条边界链接即可整链拼接，数据结点不移动、不申请。 */
int DListConcat(DLinkList dest, DLinkList src)
{
    if (dest == NULL || src == NULL || dest == src)
    {
        return DLIST_ERR;
    }
    if (src->next == src)
    {
        return DLIST_OK;
    }
    DListNode *tail = dest->prev;
    DListNode *first = src->next;
    DListNode *last = src->prev;
    tail->next = first;
    first->prev = tail;
    last->next = dest;
    dest->prev = last;
    src->next = src;
    src->prev = src;
    return DLIST_OK;
}

int DListMergeSorted(DLinkList dest, DLinkList a, DLinkList b)
{
    if (dest == NULL || a == NULL || b == NULL
        || dest == a || dest == b || a == b || !DListEmpty(dest))
    {
        return DLIST_ERR;
    }
    if (!IsSorted(a) || !IsSorted(b))
    {
        return DLIST_ERR;
    }
    while (!DListEmpty(a) && !DListEmpty(b))
    {
        DListNode *node;
        if (a->next->data <= b->next->data)
        {
            node = a->next;
        }
        else
        {
            node = b->next;
        }
        Unlink(node);
        LinkBefore(dest, node);
    }
    DListConcat(dest, a);
    DListConcat(dest, b);
    return DLIST_OK;
}

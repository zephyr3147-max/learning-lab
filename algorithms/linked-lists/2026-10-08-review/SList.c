#include "SList.h"
#include <stdio.h>
#include <stdlib.h>

/* 仅测试构建替换 malloc，用于确定性模拟分配失败。 */
#ifdef SLIST_TEST_ALLOCATOR
void *SListTestMalloc(size_t bytes);
#define SLIST_MALLOC SListTestMalloc
#else
#define SLIST_MALLOC malloc
#endif

/* 文件内部助手，不在头文件中公开。 */
static SListNode *BuyNode(ElemType value)
{
    SListNode *node = SLIST_MALLOC(sizeof(*node));
    if (node != NULL)
    {
        node->data = value;
        node->next = NULL;
    }
    return node;
}

static SListNode *FindPrev(LinkList L, int i)
{
    if (L == NULL || i < 1)
    {
        return NULL;
    }
    SListNode *p = L;
    for (int j = 0; j < i - 1 && p != NULL; ++j)
    {
        p = p->next;
    }
    return p;
}

static const SListNode *FindNode(const SListNode *L, int i)
{
    if (L == NULL || i < 1)
    {
        return NULL;
    }
    const SListNode *p = L->next;
    for (int j = 1; j < i && p != NULL; ++j)
    {
        p = p->next;
    }
    return p;
}

static int InsertAfter(SListNode *prev, ElemType value)
{
    if (prev == NULL)
    {
        return SLIST_ERR;
    }
    SListNode *node = BuyNode(value);
    if (node == NULL)
    {
        return SLIST_ERR;
    }
    node->next = prev->next;
    prev->next = node;
    return SLIST_OK;
}

static int EraseAfter(SListNode *prev, ElemType *outValue)
{
    if (prev == NULL || prev->next == NULL)
    {
        return SLIST_ERR;
    }
    SListNode *node = prev->next;
    if (outValue != NULL)
    {
        *outValue = node->data;
    }
    prev->next = node->next;
    free(node);
    return SLIST_OK;
}

static int IsSorted(const SListNode *L)
{
    for (const SListNode *p = L->next; p != NULL && p->next != NULL; p = p->next)
    {
        if (p->data > p->next->data)
        {
            return 0;
        }
    }
    return 1;
}

/* ① 生命周期与基本查询 */
int SListInit(LinkList *L)
{
    if (L == NULL || *L != NULL)
    {
        return SLIST_ERR;
    }
    SListNode *head = BuyNode(0);
    if (head == NULL)
    {
        return SLIST_ERR;
    }
    *L = head;
    return SLIST_OK;
}

int SListEmpty(const SListNode *L)
{
    return L != NULL && L->next == NULL;
}

int SListLength(const SListNode *L)
{
    if (L == NULL)
    {
        return 0;
    }
    int n = 0;
    for (const SListNode *p = L->next; p != NULL; p = p->next)
    {
        ++n;
    }
    return n;
}

void SListPrint(const SListNode *L)
{
    if (L == NULL)
    {
        return;
    }
    for (const SListNode *p = L->next; p != NULL; p = p->next)
    {
        if (p != L->next)
        {
            printf(" ");
        }
        printf("%d", p->data);
    }
    printf("\n");
}

/* ② 取值和修改 */
int SListGetElem(const SListNode *L, int i, ElemType *outValue)
{
    const SListNode *p = FindNode(L, i);
    if (p == NULL || outValue == NULL)
    {
        return SLIST_ERR;
    }
    *outValue = p->data;
    return SLIST_OK;
}

int SListSetElem(LinkList L, int i, ElemType value)
{
    SListNode *prev = FindPrev(L, i);
    if (prev == NULL || prev->next == NULL)
    {
        return SLIST_ERR;
    }
    prev->next->data = value;
    return SLIST_OK;
}

/* ③ 查找与相邻元素 */
int SListLocateElem(const SListNode *L, ElemType value)
{
    if (L == NULL)
    {
        return 0;
    }
    int i = 0;
    for (const SListNode *p = L->next; p != NULL; p = p->next)
    {
        ++i;
        if (p->data == value)
        {
            return i;
        }
    }
    return 0;
}

int SListPriorElem(const SListNode *L, ElemType value, ElemType *outValue)
{
    if (L == NULL || outValue == NULL)
    {
        return SLIST_ERR;
    }
    const SListNode *prev = L;
    const SListNode *p = L->next;
    while (p != NULL && p->data != value)
    {
        prev = p;
        p = p->next;
    }
    if (p == NULL || prev == L)
    {
        return SLIST_ERR;
    }
    *outValue = prev->data;
    return SLIST_OK;
}

int SListNextElem(const SListNode *L, ElemType value, ElemType *outValue)
{
    if (L == NULL || outValue == NULL)
    {
        return SLIST_ERR;
    }
    const SListNode *p = L->next;
    while (p != NULL && p->data != value)
    {
        p = p->next;
    }
    if (p == NULL || p->next == NULL)
    {
        return SLIST_ERR;
    }
    *outValue = p->next->data;
    return SLIST_OK;
}

/* ④ 三种插入共享 InsertAfter，不重复写链接操作。 */
int SListInsert(LinkList L, int i, ElemType value)
{
    return InsertAfter(FindPrev(L, i), value);
}

int SListPushFront(LinkList L, ElemType value)
{
    return SListInsert(L, 1, value);
}

int SListPushBack(LinkList L, ElemType value)
{
    if (L == NULL)
    {
        return SLIST_ERR;
    }
    SListNode *tail = L;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    return InsertAfter(tail, value);
}

/* ⑤ 删除时均由 EraseAfter 完成断链和释放。 */
int SListDelete(LinkList L, int i, ElemType *outValue)
{
    return EraseAfter(FindPrev(L, i), outValue);
}

int SListPopFront(LinkList L, ElemType *outValue)
{
    return SListDelete(L, 1, outValue);
}

int SListPopBack(LinkList L, ElemType *outValue)
{
    if (L == NULL || L->next == NULL)
    {
        return SLIST_ERR;
    }
    SListNode *prev = L;
    while (prev->next->next != NULL)
    {
        prev = prev->next;
    }
    return EraseAfter(prev, outValue);
}

/* ⑥ 边寻找边删除，避免先 Locate 再按位 Delete 的第二次遍历。 */
int SListDeleteValue(LinkList L, ElemType value)
{
    if (L == NULL)
    {
        return SLIST_ERR;
    }
    SListNode *prev = L;
    while (prev->next != NULL && prev->next->data != value)
    {
        prev = prev->next;
    }
    return EraseAfter(prev, NULL);
}

int SListRemoveAll(LinkList L, ElemType value)
{
    if (L == NULL)
    {
        return 0;
    }
    int removed = 0;
    SListNode *prev = L;
    while (prev->next != NULL)
    {
        if (prev->next->data == value)
        {
            EraseAfter(prev, NULL);
            ++removed;
            /* 删除后 prev 不前进，继续检查新的后继。 */
        }
        else
        {
            prev = prev->next;
        }
    }
    return removed;
}

/* ⑦ 临时链尾插建表，全部成功后才清空原表。 */
int SListAssign(LinkList L, const ElemType a[], int n)
{
    if (L == NULL || n < 0 || (n > 0 && a == NULL))
    {
        return SLIST_ERR;
    }
    SListNode dummy = {0, NULL};
    SListNode *tail = &dummy;
    for (int i = 0; i < n; ++i)
    {
        SListNode *node = BuyNode(a[i]);
        if (node == NULL)
        {
            SListClear(&dummy);
            return SLIST_ERR;
        }
        tail->next = node;
        tail = node;
    }
    SListClear(L);
    L->next = dummy.next;
    return SLIST_OK;
}

void SListClear(LinkList L)
{
    if (L == NULL)
    {
        return;
    }
    SListNode *p = L->next;
    while (p != NULL)
    {
        SListNode *next = p->next;
        free(p);
        p = next;
    }
    L->next = NULL;
}

void SListDestroy(LinkList *L)
{
    if (L == NULL || *L == NULL)
    {
        return;
    }
    SListClear(*L);
    free(*L);
    *L = NULL;
}

/* ⑧ 只改变 next 的迭代逆置。 */
void SListReverse(LinkList L)
{
    if (L == NULL)
    {
        return;
    }
    SListNode *prev = NULL;
    SListNode *current = L->next;
    while (current != NULL)
    {
        SListNode *next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    L->next = prev;
}

int SListMiddle(const SListNode *L, ElemType *outValue)
{
    if (L == NULL || L->next == NULL || outValue == NULL)
    {
        return SLIST_ERR;
    }
    const SListNode *slow = L->next;
    const SListNode *fast = L->next;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    *outValue = slow->data;
    return SLIST_OK;
}

int SListKthFromEnd(const SListNode *L, int k, ElemType *outValue)
{
    if (L == NULL || k < 1 || outValue == NULL)
    {
        return SLIST_ERR;
    }
    const SListNode *fast = L->next;
    const SListNode *slow = L->next;
    for (int i = 0; i < k; ++i)
    {
        if (fast == NULL)
        {
            return SLIST_ERR;
        }
        fast = fast->next;
    }
    while (fast != NULL)
    {
        fast = fast->next;
        slow = slow->next;
    }
    *outValue = slow->data;
    return SLIST_OK;
}

/* ⑨ 三张表头保留，数据结点从 a/b 转移到 dest。 */
int SListMergeSorted(LinkList dest, LinkList a, LinkList b)
{
    if (dest == NULL || a == NULL || b == NULL
        || dest == a || dest == b || a == b || dest->next != NULL)
    {
        return SLIST_ERR;
    }
    if (!IsSorted(a) || !IsSorted(b))
    {
        return SLIST_ERR;
    }
    SListNode *tail = dest;
    SListNode *pa = a->next;
    SListNode *pb = b->next;
    while (pa != NULL && pb != NULL)
    {
        if (pa->data <= pb->data)
        {
            tail->next = pa;
            pa = pa->next;
        }
        else
        {
            tail->next = pb;
            pb = pb->next;
        }
        tail = tail->next;
    }
    tail->next = pa != NULL ? pa : pb;
    a->next = NULL;
    b->next = NULL;
    return SLIST_OK;
}

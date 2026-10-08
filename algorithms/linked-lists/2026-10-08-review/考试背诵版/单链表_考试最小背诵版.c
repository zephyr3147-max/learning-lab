#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;
typedef Node *LinkList;

/* 初始化：申请头结点，建立带头结点的空表。O(1)。
 * L：头指针变量的地址，调用前该变量必须为 NULL。
 * 成功返回 1；参数非法、重复初始化或分配失败返回 0。
 */
int InitList(LinkList *L)
{
    if (L == NULL || *L != NULL)
    {
        return 0;
    }
    *L = malloc(sizeof(Node));
    if (*L == NULL)
    {
        return 0;
    }
    (*L)->next = NULL;
    return 1;
}

/* 按位取值：读取第 i 个数据结点，不改变原表。最坏 O(n)。
 * L：头结点地址；i：位置（1..n）；e：表外接收变量的地址。
 * 成功返回 1，失败返回 0 且不修改输出值。
 */
int GetElem(const Node *L, int i, ElemType *e)
{
    if (L == NULL || i < 1 || e == NULL)
    {
        return 0;
    }
    const Node *p = L->next;
    for (int j = 1; j < i && p != NULL; ++j)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        return 0;
    }
    *e = p->data;
    return 1;
}

/* 按值查找：查找第一个值等于 e 的数据结点。最坏 O(n)。
 * L：头结点地址；e：要查找的值。
 * 返回从 1 开始的位置；未找到或 L 为 NULL 返回 0。
 */
int LocateElem(const Node *L, ElemType e)
{
    if (L == NULL)
    {
        return 0;
    }
    int i = 1;
    for (const Node *p = L->next; p != NULL; p = p->next)
    {
        if (p->data == e)
        {
            return i;
        }
        ++i;
    }
    return 0;
}

/* 插入：在第 i 个位置插入 e，先找第 i-1 个结点。最坏 O(n)。
 * L：头结点地址；i：位置（1..n+1）；e：新元素。
 * 成功返回 1；位置非法或分配失败返回 0，原表不变。
 */
int ListInsert(LinkList L, int i, ElemType e)
{
    if (L == NULL || i < 1)
    {
        return 0;
    }
    Node *p = L;
    for (int j = 0; j < i - 1 && p != NULL; ++j)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        return 0;
    }
    Node *s = malloc(sizeof(Node));
    if (s == NULL)
    {
        return 0;
    }
    s->data = e;
    s->next = p->next;
    p->next = s;
    return 1;
}

/* 删除：删除第 i 个数据结点，先找它的前驱。最坏 O(n)。
 * L：头结点地址；i：位置（1..n）；e：表外接收变量的地址，
 * 可传 NULL 表示不接收。成功返回 1，失败返回 0 且原表不变。
 */
int ListDelete(LinkList L, int i, ElemType *e)
{
    if (L == NULL || i < 1)
    {
        return 0;
    }
    Node *p = L;
    for (int j = 0; j < i - 1 && p != NULL; ++j)
    {
        p = p->next;
    }
    if (p == NULL || p->next == NULL)
    {
        return 0;
    }
    Node *q = p->next;
    if (e != NULL)
    {
        *e = q->data;
    }
    p->next = q->next;
    free(q);
    return 1;
}

/* 遍历输出：依次打印数据结点，不打印头结点。O(n)。
 * L：头结点地址；不改原表，无返回值。空表输出换行。
 */
void PrintList(const Node *L)
{
    if (L == NULL)
    {
        return;
    }
    for (const Node *p = L->next; p != NULL; p = p->next)
    {
        if (p != L->next)
        {
            printf(" ");
        }
        printf("%d", p->data);
    }
    printf("\n");
}

/* 销毁：释放所有数据结点和头结点，再把外部头指针置为 NULL。
 * L：头指针变量的地址；可重复调用，无返回值。O(n)。
 */
void DestroyList(LinkList *L)
{
    if (L == NULL)
    {
        return;
    }
    Node *p = *L;
    while (p != NULL)
    {
        Node *next = p->next;
        free(p);
        p = next;
    }
    *L = NULL;
}

/* 调用示例：这部分帮助理解接口，不必逐字背诵。 */
int main(void)
{
    LinkList L = NULL;
    ElemType e;
    if (InitList(&L) == 0)
    {
        return 1;
    }
    if (ListInsert(L, 1, 10) == 0 || ListInsert(L, 2, 30) == 0
        || ListInsert(L, 2, 20) == 0)
    {
        DestroyList(&L);
        return 1;
    }
    PrintList(L);
    if (ListDelete(L, 2, &e) == 0)
    {
        DestroyList(&L);
        return 1;
    }
    printf("deleted: %d\n", e);
    PrintList(L);
    if (GetElem(L, 2, &e) == 0)
    {
        DestroyList(&L);
        return 1;
    }
    printf("second: %d\n", e);
    printf("position of 30: %d\n", LocateElem(L, 30));
    DestroyList(&L);
    return 0;
}

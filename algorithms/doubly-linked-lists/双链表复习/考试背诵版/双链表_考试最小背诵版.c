#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct Node
{
    ElemType data;
    struct Node* prev;
    struct Node* next;
} Node;
typedef Node* DLinkList;

/* 初始化：申请头结点，让 prev/next 都指回自身。O(1)。
 * 参数为外部头指针地址，调用前头指针必须为 NULL。
 * 成功返回 1，参数非法、重复初始化或分配失败返回 0。
 */
int InitList(DLinkList* L)
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
    (*L)->prev = *L;
    (*L)->next = *L;
    return 1;
}

/* 取第 i 个数据元素：位置为 1..n，e 接收结果。最坏 O(n)。
 * 成功返回 1，失败返回 0 且不修改输出。
 */
int GetElem(const Node* L, int i, ElemType* e)
{
    if (L == NULL || i < 1 || e == NULL)
    {
        return 0;
    }
    const Node* p = L->next;
    int j = 1;
    while (p != L && j < i)
    {
        p = p->next;
        ++j;
    }
    if (p == L)
    {
        return 0;
    }
    *e = p->data;
    return 1;
}

/* 查找第一个等于 e 的值，返回从 1 开始的位置或 0。最坏 O(n)。 */
int LocateElem(const Node* L, ElemType e)
{
    int i = 0;
    for (const Node* p = L->next; p != L; p = p->next)
    {
        ++i;
        if (p->data == e)
        {
            return i;
        }
    }
    return 0;
}

/* 在第 i 个位置插入 e：合法范围 1..n+1。最坏 O(n)。
 * 成功返回 1；位置非法或分配失败返回 0，原表不变。
 */
int ListInsert(DLinkList L, int i, ElemType e)
{
    if (L == NULL || i < 1)
    {
        return 0;
    }
    Node* p = L->next;
    int j = 1;
    while (p != L && j < i)
    {
        p = p->next;
        ++j;
    }
    if (j != i)
    {
        return 0;
    }
    Node* s = malloc(sizeof(Node));
    if (s == NULL)
    {
        return 0;
    }
    Node* prev = p->prev;

    s->data = e;
    s->prev = prev;
    s->next = p;
    prev->next = s;
    p->prev = s;
    return 1;
}

/* 删除第 i 个数据结点，e 接收被删值，可传 NULL。最坏 O(n)。
 * 成功返回 1；位置非法返回 0，原表和输出值不变。
 */
int ListDelete(DLinkList L, int i, ElemType* e)
{
    if (L == NULL || i < 1)
    {
        return 0;
    }
    Node* p = L->next;
    int j = 1;
    while (p != L && j < i)
    {
        p = p->next;
        ++j;
    }
    if (p == L)
    {
        return 0;
    }
    if (e != NULL)
    {
        *e = p->data;
    }
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
    return 1;
}

/* 正向输出：不打印头结点，遇到头结点停止。O(n)。 */
void PrintList(const Node* L)
{
    for (const Node* p = L->next; p != L; p = p->next)
    {
        if (p != L->next)
        {
            printf(" ");
        }
        printf("%d", p->data);
    }
    printf("\n");
}

/* 销毁：先释放数据结点，再释放头结点，外部头指针置 NULL。O(n)。 */
void DestroyList(DLinkList* L)
{
    if (L == NULL || *L == NULL)
    {
        return;
    }
    Node* p = (*L)->next;
    while (p != *L)
    {
        Node* next = p->next;
        free(p);
        p = next;
    }
    free(*L);
    *L = NULL;
}

/* 自动演示；考试按题目要求改写 main。 */
int main(void)
{
    DLinkList L = NULL;
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

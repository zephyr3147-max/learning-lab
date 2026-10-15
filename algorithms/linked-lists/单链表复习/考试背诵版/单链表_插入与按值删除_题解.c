// 【问题描述】创建链式线性表进行输入插入 寻找  删除 与 输出功能
// 【输入形式】1 输入元素个数  2 输入数据 3 插入位置与插入元素 4 输入删除要删除的元素
// 【输出形式】输出线性表
// 【样例输入】

// 5                  //输入元素个数

// 1 2 3 4 5      //输入数据

// 3 6              //插入位置与插入元素 如果插入位置不在范围内则不插入继续运行

// 4             // 输入删除要删除的元素
// 【样例输出】

// 1 2 6 3 5
// 【样例说明】
// 【评分标准】


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;

/* 创建数据结点：失败返回 NULL。 */
Node *CreateNode(ElemType e)
{
    Node *p = malloc(sizeof(Node));
    if (p != NULL)
    {
        p->data = e;
        p->next = NULL;
    }
    return p;
}

/* 按位置插入：成功 1，位置非法 0，申请失败 -1。 */
int ListInsert(Node *head, int i, ElemType e)
{
    if (i < 1)
    {
        return 0;
    }
    Node *p = head;
    int j = 0;
    /* 头结点位置为 0，找第 i 个位置的前驱。 */
    while (p != NULL && j < i - 1)
    {
        p = p->next;
        ++j;
    }
    if (p == NULL)
    {
        return 0;
    }
    Node *s = CreateNode(e);
    if (s == NULL)
    {
        return -1;
    }
    s->next = p->next;
    p->next = s;
    return 1;
}

/* 查找第一个等于 e 的元素，返回前驱；未找到返回 NULL。 */
Node *FindPrev(Node *head, ElemType e)
{
    Node *p = head;
    while (p->next != NULL)
    {
        if (p->next->data == e)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

/* 按值删除第一个匹配结点；未找到不改表。 */
int DeleteValue(Node *head, ElemType e)
{
    Node *p = FindPrev(head, e);
    if (p == NULL)
    {
        return 0;
    }
    Node *q = p->next;
    p->next = q->next;
    free(q);
    return 1;
}

/* 输出数据元素，不输出头结点，无末尾多余空格。 */
void PrintList(const Node *head)
{
    const Node *p = head->next;
    while (p != NULL)
    {
        printf("%d", p->data);
        if (p->next != NULL)
        {
            printf(" ");
        }
        p = p->next;
    }
    printf("\n");
}

/* 释放全部数据结点，保留头结点。 */
void ClearList(Node *head)
{
    Node *p = head->next;
    while (p != NULL)
    {
        Node *next = p->next;
        free(p);
        p = next;
    }
    head->next = NULL;
}

int main(void)
{
    /* 局部头结点不需要 malloc，也不能 free(&head)。 */
    Node head = {0, NULL};
    Node *tail = &head;
    int n;
    if (scanf("%d", &n) != 1 || n < 0)
    {
        return 0;
    }
    /* 保留尾指针，每个元素录入 O(1)。 */
    for (int i = 0; i < n; ++i)
    {
        ElemType e;
        if (scanf("%d", &e) != 1)
        {
            ClearList(&head);
            return 0;
        }
        Node *s = CreateNode(e);
        if (s == NULL)
        {
            ClearList(&head);
            return 1;
        }
        tail->next = s;
        tail = s;
    }
    int position;
    ElemType value;
    if (scanf("%d %d", &position, &value) != 2)
    {
        ClearList(&head);
        return 0;
    }
    /* 非法位置不退出；申请失败才退出。 */
    if (ListInsert(&head, position, value) == -1)
    {
        ClearList(&head);
        return 1;
    }
    ElemType target;
    if (scanf("%d", &target) != 1)
    {
        ClearList(&head);
        return 0;
    }
    DeleteValue(&head, target);
    PrintList(&head);
    ClearList(&head);
    return 0;
}


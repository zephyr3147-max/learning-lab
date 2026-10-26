#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
 * 线性表 链式结构
 * 输入：n；n 个元素；插入位置和插入元素；待删除元素。
 * 输出：处理后的线性表，元素间一个空格。
 * 约定：带头结点，位序从 1 开始；插入范围 1 ~ n+1，越界不插入并继续。
 */

typedef struct Node
{
    int data;
    struct Node* next;
} Node;

/* 在第 pos 个位置前插入 value；越界时不插入。O(n)。 */
void Insert(Node* head, int pos, int value)
{
    Node* p = head;
    Node* s = NULL;
    if (pos < 1)
    {
        return;
    }
    while (pos > 1 && p->next != NULL)
    {
        p = p->next;
        --pos;
    }
    if (pos > 1)
    {
        return;
    }
    s = (Node*)malloc(sizeof(Node));
    s->data = value;
    s->next = p->next;
    p->next = s;
}

/* 删除第一个值为 value 的结点；不存在时链表不变。O(n)。 */
void DeleteValue(Node* head, int value)
{
    Node* p = head;
    while (p->next != NULL)
    {
        if (p->next->data == value)
        {
            Node* q = p->next;
            p->next = q->next;
            free(q);
            return;
        }
        p = p->next;
    }
}

/* 查找第一个值为 value 的结点位序，找不到返回 0。O(n)。 */
int Locate(Node* head, int value)
{
    Node* p = head->next;
    int i = 1;
    while (p != NULL)
    {
        if (p->data == value)
        {
            return i;
        }
        p = p->next;
        ++i;
    }
    return 0;
}

/* 输出数据结点，元素间一个空格，末尾换行。O(n)。 */
void PrintList(Node* head)
{
    Node* p = head->next;
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

int main(void)
{
    Node head = {0, NULL};
    Node* tail = &head;
    int n = 0;
    int pos = 0;
    int value = 0;
    int target = 0;

    /* 尾插建表：tail 始终指向表尾，整体 O(n)。 */
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        Node* s = NULL;
        scanf("%d", &value);
        s = (Node*)malloc(sizeof(Node));
        s->data = value;
        s->next = NULL;
        tail->next = s;
        tail = s;
    }

    scanf("%d %d", &pos, &value);
    Insert(&head, pos, value);   /* 位置越界时不插入，程序继续 */

    scanf("%d", &target);
    DeleteValue(&head, target);

    PrintList(&head);
    return 0;
}

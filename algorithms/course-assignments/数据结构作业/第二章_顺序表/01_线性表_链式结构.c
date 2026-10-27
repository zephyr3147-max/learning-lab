#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
} Node;

/* 创建一个数据结点。 */
Node* CreateNode(int value)
{
    Node* s = (Node*)malloc(sizeof(Node));
    if (s == NULL)
    {
        exit(1);
    }
    s->data = value;
    s->next = NULL;
    return s;
}

/* 尾插读入 n 个元素，head 指向空表的头结点。O(n)。 */
void ReadList(Node* head, int n)
{
    Node* tail = head;
    int value;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &value);
        Node* s = CreateNode(value);
        tail->next = s;
        tail = s;
    }
}

/* 在第 pos 个位置前插入，越界不插入。O(n)。 */
void Insert(Node* head, int pos, int value)
{
    Node* p = head;
    if (pos < 1)
    {
        return;
    }
    for (int i = 1; i < pos && p != NULL; ++i)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        return;
    }
    Node* s = CreateNode(value);
    s->next = p->next; /* 先保存后继，再接入新结点。 */
    p->next = s;
}

/* 按值查找第一个匹配元素，返回位序；未找到返回 0。O(n)。 */
int Locate(const Node* head, int value)
{
    const Node* p = head->next;
    int pos = 1;
    while (p != NULL)
    {
        if (p->data == value)
        {
            return pos;
        }
        p = p->next;
        ++pos;
    }
    return 0;
}

/* 删除第一个值为 value 的结点。O(n)。 */
void DeleteValue(Node* head, int value)
{
    Node* p = head;
    while (p->next != NULL && p->next->data != value)
    {
        p = p->next;
    }
    if (p->next != NULL)
    {
        Node* q = p->next;
        p->next = q->next;
        free(q);
    }
}

/* 输出数据结点，元素间一个空格。O(n)。 */
void PrintList(const Node* head)
{
    const Node* p = head->next;
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
    int n;
    int pos;
    int value;
    int target;
    scanf("%d", &n);
    ReadList(&head, n);
    scanf("%d%d", &pos, &value);
    Insert(&head, pos, value);
    scanf("%d", &target);
    DeleteValue(&head, target);
    PrintList(&head);
    return 0;
}

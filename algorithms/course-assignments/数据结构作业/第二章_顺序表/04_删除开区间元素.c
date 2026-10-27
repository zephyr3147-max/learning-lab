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

/* 尾插建表，以 -1 结束；head 指向空表的头结点。O(n)。 */
void ReadList(Node* head)
{
    Node* tail = head;
    int value;
    while (scanf("%d", &value) == 1 && value != -1)
    {
        Node* s = CreateNode(value);
        tail->next = s;
        tail = s;
    }
}

/* 删除开区间内的结点，两个端点保留。O(n)。 */
void DeleteRange(Node* head, int mink, int maxk)
{
    Node* p = head;
    while (p->next != NULL && p->next->data <= mink)
    {
        p = p->next;
    }
    while (p->next != NULL && p->next->data < maxk)
    {
        Node* q = p->next;
        p->next = q->next;
        free(q); /* 删除后前驱 p 不移动，继续检查新后继。 */
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
    int mink;
    int maxk;
    ReadList(&head);
    scanf("%d%d", &mink, &maxk);
    DeleteRange(&head, mink, maxk);
    PrintList(&head);
    return 0;
}

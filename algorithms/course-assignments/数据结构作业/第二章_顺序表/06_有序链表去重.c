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

/* 尾插建表，读到 EOF，-1 也是普通数据；head 指向空表的头结点。O(n)。 */
void ReadList(Node* head)
{
    Node* tail = head;
    int value;
    while (scanf("%d", &value) == 1)
    {
        Node* s = CreateNode(value);
        tail->next = s;
        tail = s;
    }
}

/* 有序表中相同值相邻，每个值只保留一次。O(n)。 */
void Deduplicate(Node* head)
{
    Node* p = head->next;
    while (p != NULL && p->next != NULL)
    {
        if (p->data == p->next->data)
        {
            Node* q = p->next;
            p->next = q->next;
            free(q); /* p 不前进，避免漏删连续重复值。 */
        }
        else
        {
            p = p->next;
        }
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
    ReadList(&head);
    Deduplicate(&head);
    PrintList(&head);
    return 0;
}

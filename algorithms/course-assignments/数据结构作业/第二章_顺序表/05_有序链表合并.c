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

/* a、b 指向首个数据结点；按升序合并，保留重复值。O(m+n)。 */
Node* Merge(Node* a, Node* b)
{
    Node head = {0, NULL};
    Node* tail = &head;
    while (a != NULL && b != NULL)
    {
        if (a->data <= b->data)
        {
            tail->next = a;
            a = a->next;
        }
        else
        {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = a != NULL ? a : b;
    return head.next;
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
    Node A = {0, NULL};
    Node B = {0, NULL};
    Node C = {0, NULL};
    ReadList(&A);
    ReadList(&B);
    C.next = Merge(A.next, B.next);
    PrintList(&C);
    return 0;
}

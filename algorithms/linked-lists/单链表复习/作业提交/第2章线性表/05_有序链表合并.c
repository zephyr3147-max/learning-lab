#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

static Node *ReadList(void)
{
    Node head = {0, NULL};
    Node *tail = &head;
    int value;
    while (scanf("%d", &value) == 1 && value != -1)
    {
        Node *node = malloc(sizeof(*node));
        if (node == NULL)
        {
            exit(EXIT_FAILURE);
        }
        node->data = value;
        node->next = NULL;
        tail->next = node;
        tail = node;
    }
    return head.next;
}

/* Reuse the nodes of both lists; O(m+n) time, O(1) auxiliary space. */
static Node *MergeSorted(Node *a, Node *b)
{
    Node head = {0, NULL};
    Node *tail = &head;
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

int main(void)
{
    Node *a = ReadList();
    Node *b = ReadList();
    Node *p = MergeSorted(a, b);
    int first = 1;
    while (p != NULL)
    {
        Node *next = p->next;
        printf("%s%d", first ? "" : " ", p->data);
        first = 0;
        free(p);
        p = next;
    }
    putchar('\n');
    return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

/* A sentinel head allows deletion of the first data node. */
static void DeleteRange(Node *head, int mink, int maxk)
{
    Node *prev = head;
    while (prev->next != NULL && prev->next->data <= mink)
    {
        prev = prev->next;
    }
    while (prev->next != NULL && prev->next->data < maxk)
    {
        Node *deleted = prev->next;
        prev->next = deleted->next;
        free(deleted);
    }
}

int main(void)
{
    Node head = {0, NULL};
    Node *tail = &head;
    int value;
    while (scanf("%d", &value) == 1 && value != -1)
    {
        Node *node = malloc(sizeof(*node));
        if (node == NULL)
        {
            return EXIT_FAILURE;
        }
        node->data = value;
        node->next = NULL;
        tail->next = node;
        tail = node;
    }
    int mink, maxk;
    if (scanf("%d%d", &mink, &maxk) != 2)
    {
        return EXIT_FAILURE;
    }
    if (mink < maxk)
    {
        DeleteRange(&head, mink, maxk);
    }
    /* Linear scan: O(n) time, O(1) auxiliary space. */
    Node *p = head.next;
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

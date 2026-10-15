#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

/* Accept spaces, ASCII commas and UTF-8 Chinese commas. */
static int ReadInt(int *value)
{
    int ch;
    do
    {
        ch = getchar();
    } while (ch != EOF && ch != '-' && (ch < '0' || ch > '9'));
    if (ch == EOF)
    {
        return 0;
    }
    int sign = 1;
    if (ch == '-')
    {
        sign = -1;
        ch = getchar();
    }
    if (ch < '0' || ch > '9')
    {
        return 0;
    }
    int result = 0;
    do
    {
        result = result * 10 + ch - '0';
        ch = getchar();
    } while (ch >= '0' && ch <= '9');
    *value = sign * result;
    return 1;
}

static Node *ReadList(int count)
{
    Node head = {0, NULL};
    Node *tail = &head;
    for (int i = 0; i < count; ++i)
    {
        Node *node = malloc(sizeof(*node));
        if (node == NULL)
        {
            exit(EXIT_FAILURE);
        }
        if (!ReadInt(&node->data))
        {
            free(node);
            exit(EXIT_FAILURE);
        }
        node->next = NULL;
        tail->next = node;
        tail = node;
    }
    return head.next;
}

/* Transfer existing nodes; O(m+n) time and O(1) auxiliary space. */
static Node *MergeAlternating(Node *a, Node *b)
{
    Node head = {0, NULL};
    Node *tail = &head;
    while (a != NULL && b != NULL)
    {
        tail->next = a;
        a = a->next;
        tail = tail->next;
        tail->next = b;
        b = b->next;
        tail = tail->next;
    }
    tail->next = a != NULL ? a : b;
    return head.next;
}

int main(void)
{
    int m, n;
    if (!ReadInt(&m) || !ReadInt(&n) || m < 0 || n < 0)
    {
        return EXIT_FAILURE;
    }
    Node *a = ReadList(m);
    Node *b = ReadList(n);
    Node *p = MergeAlternating(a, b);
    int first = 1;
    while (p != NULL)
    {
        Node *next = p->next;
        printf("%s%d", first ? "" : "\xEF\xBC\x8C", p->data);
        first = 0;
        free(p);
        p = next;
    }
    putchar('\n');
    return 0;
}

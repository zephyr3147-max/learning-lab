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

/* 跳过逗号等分隔符，再读取整数；本题输入也可用空格分隔。 */
int ReadInt(void)
{
    int value;
    scanf("%*[^0-9-]");
    scanf("%d", &value);
    return value;
}

/* 尾插读入 n 个元素，head 指向空表的头结点。O(n)。 */
void ReadList(Node* head, int n)
{
    Node* tail = head;
    int value;
    for (int i = 0; i < n; ++i)
    {
        value = ReadInt();
        Node* s = CreateNode(value);
        tail->next = s;
        tail = s;
    }
}

/* a、b 指向首个数据结点；复用原结点交替合并。O(m+n)。 */
Node* Merge(Node* a, Node* b)
{
    Node head = {0, NULL};
    Node* tail = &head;
    while (a != NULL && b != NULL)
    {
        tail->next = a;
        a = a->next;
        tail = tail->next;
        tail->next = b;
        b = b->next;
        tail = tail->next;
    }
    tail->next = a != NULL ? a : b; /* 接上剩余的一整段。 */
    return head.next;
}

/* 输出数据结点，元素间中文逗号。O(n)。 */
void PrintList(const Node* head)
{
    const Node* p = head->next;
    while (p != NULL)
    {
        printf("%d", p->data);
        if (p->next != NULL)
        {
            printf("，");
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
    int m = ReadInt();
    int n = ReadInt();
    ReadList(&A, m);
    ReadList(&B, n);
    C.next = Merge(A.next, B.next);
    PrintList(&C);
    return 0;
}

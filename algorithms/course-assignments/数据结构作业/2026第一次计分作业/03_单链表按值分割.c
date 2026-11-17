#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node* next;
} Node;

/* 用两个哨兵尾插分链，保持两段内部次序，时间 O(n)。 */
Node* Partition(Node* head, int pivot)
{
    Node lessDummy;
    Node greaterDummy;
    lessDummy.next = NULL;
    greaterDummy.next = NULL;
    Node* lessTail = &lessDummy;
    Node* greaterTail = &greaterDummy;
    Node* current = head;

    while (current != NULL)
    {
        /* 先保存后继，再改 current->next，防止断链。 */
        Node* next = current->next;
        current->next = NULL;
        if (current->value < pivot)
        {
            lessTail->next = current;
            lessTail = current;
        }
        else
        {
            greaterTail->next = current;
            greaterTail = current;
        }
        current = next;
    }

    /* 第一段为空时，表头取第二段的第一个结点。 */
    lessTail->next = greaterDummy.next;
    if (lessDummy.next != NULL)
    {
        return lessDummy.next;
    }
    return greaterDummy.next;
}

int main(void)
{
    int n;
    int pivot;
    scanf("%d %d", &n, &pivot);

    /* 题面链表带头结点，先建头结点，再尾插数据结点。 */
    Node dummyHead;
    dummyHead.next = NULL;
    Node* tail = &dummyHead;
    for (int i = 0; i < n; ++i)
    {
        int value;
        scanf("%d", &value);

        Node* node = (Node*)malloc(sizeof(Node));
        if (node == NULL)
        {
            break;
        }
        node->value = value;
        node->next = NULL;
        tail->next = node;
        tail = node;
    }

    Node* head = Partition(dummyHead.next, pivot);

    /* 顺序输出并释放所有数据结点。 */
    while (head != NULL)
    {
        printf("%d", head->value);
        if (head->next != NULL)
        {
            printf(" ");
        }
        Node* next = head->next;
        free(head);
        head = next;
    }

    printf("\n");
    return 0;
}

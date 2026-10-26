#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

/* 逆序输入，头插法建立升序链表。head 必须是空表的头结点。 */
int CreateList(Node* head)
{
    int n;
    int value;

    if (scanf("%d", &n) != 1 || n < 0) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &value) != 1) {
            return 0;
        }

        Node* s = (Node*)malloc(sizeof(Node));
        if (s == NULL) {
            return 0;
        }

        s->data = value;
        s->next = head->next;
        head->next = s;
    }

    return 1;
}

/* A、B 是互不共享数据结点的升序表，C 是独立的空表。 */
void MergeList(Node* A, Node* B, Node* C)
{
    Node* p = A->next;
    Node* q = B->next;
    Node* tail = C;

    while (p != NULL && q != NULL) {
        if (p->data <= q->data) {
            tail->next = p;
            p = p->next;
        } else {
            tail->next = q;
            q = q->next;
        }

        tail = tail->next;
    }

    if (p != NULL) {
        tail->next = p;
    } else {
        tail->next = q;
    }

    /* 数据结点统一归 C 管理，避免通过 A、B 再次释放。 */
    A->next = NULL;
    B->next = NULL;
}

void PrintList(const Node* head)
{
    const Node* p = head->next;

    printf("The current List is:\n");

    while (p != NULL) {
        printf("%d", p->data);
        if (p->next != NULL) {
            printf(",");
        }
        p = p->next;
    }

    printf("\n");
}

/* 头结点是 main 的局部变量，只释放 malloc 分配的数据结点。 */
void DestroyList(Node* head)
{
    Node* p = head->next;

    while (p != NULL) {
        Node* next = p->next;
        free(p);
        p = next;
    }

    head->next = NULL;
}

int main(void)
{
    Node A = {0, NULL};
    Node B = {0, NULL};
    Node C = {0, NULL};

    if (!CreateList(&A) || !CreateList(&B)) {
        DestroyList(&A);
        DestroyList(&B);
        return EXIT_FAILURE;
    }

    MergeList(&A, &B, &C);
    PrintList(&C);
    DestroyList(&C);

    return EXIT_SUCCESS;
}

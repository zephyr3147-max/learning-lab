   #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char* text;
    struct Node* next;
} Node;

/* 复制一个字符串到新结点；调用者负责 free 结点和 text。 */
Node* CreateNode(const char* text)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL)
    {
        exit(1);
    }
    size_t length = strlen(text);
    node->text = (char*)malloc(length + 1);
    if (node->text == NULL)
    {
        free(node);
        exit(1);
    }
    strcpy(node->text, text);
    node->next = NULL;
    return node;
}

int main(void)
{
    Node* head = CreateNode(""); /* 哨兵头结点，空队列时 head->next == head。 */
    head->next = head;
    Node* rear = head;

    char token[128];
    while (scanf("%127s", token) == 1)
    {
        Node* node = CreateNode(token);
        node->next = head; /* 新结点接在队尾，其 next 指回哨兵。 */
        rear->next = node;
        rear = node;
    }

    int first = 1;
    while (head->next != head)
    {
        Node* node = head->next;
        head->next = node->next;
        if (rear == node)
        {
            rear = head; /* 删除最后一个结点后，队列重新为空。 */
        }
        if (first == 0)
        {
            putchar(' ');
        }
        printf("%s", node->text);
        first = 0;
        free(node->text);
        free(node);
    }
    putchar('\n');

    free(head->text);
    free(head);
    return 0;
}

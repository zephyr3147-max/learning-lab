#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct QueueNode
{
    ElemType data;
    struct QueueNode* next;
} QueueNode;

/* 带头结点的链队列：front 始终指向头结点，rear 指向尾结点。
 * 空队列：front == rear，头结点的 next == NULL。
 * 非空队列：front -> 头结点 -> 第一个元素 -> ... -> 尾结点 <- rear。
 * 使用前写 LinkQueue Q = {0}；不要把结构体浅拷贝为独立队列。
 */
typedef struct
{
    QueueNode* front;
    QueueNode* rear;
} LinkQueue;

/* 初始化：申请不存放有效数据的头结点。O(1)。 */
int InitQueue(LinkQueue* Q)
{
    if (Q == NULL || Q->front != NULL || Q->rear != NULL)
    {
        return 0;
    }
    QueueNode* head = (QueueNode*)malloc(sizeof(QueueNode));
    if (head == NULL)
    {
        return 0;
    }
    head->next = NULL;
    Q->front = head;
    Q->rear = head;
    return 1;
}

/* 判空：头尾指针都指向头结点。O(1)，要求队列已初始化。 */
int QueueEmpty(const LinkQueue* Q)
{
    return Q != NULL && Q->front != NULL && Q->front == Q->rear;
}

/* 求长：从首个数据结点开始计数，不计头结点。O(n)。 */
int QueueLength(const LinkQueue* Q)
{
    if (Q == NULL || Q->front == NULL)
    {
        return 0;
    }
    int length = 0;
    for (const QueueNode* p = Q->front->next; p != NULL; p = p->next)
    {
        ++length;
    }
    return length;
}

/* 入队：尾插新结点，再更新 rear。分配失败时队列不变。O(1)。 */
int EnQueue(LinkQueue* Q, ElemType e)
{
    if (Q == NULL || Q->front == NULL)
    {
        return 0;
    }
    QueueNode* s = (QueueNode*)malloc(sizeof(QueueNode));
    if (s == NULL)
    {
        return 0;
    }
    s->data = e;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
    return 1;
}

/* 出队：删除头结点后面的首个数据结点，保留头结点。O(1)。
 * e 可为 NULL，表示只删除；失败时不修改输出变量。
 */
int DeQueue(LinkQueue* Q, ElemType* e)
{
    if (Q == NULL || Q->front == NULL || QueueEmpty(Q))
    {
        return 0;
    }
    QueueNode* p = Q->front->next;
    if (e != NULL)
    {
        *e = p->data;
    }
    Q->front->next = p->next;
    if (Q->rear == p)
    {
        /* 删除最后一个元素后，rear 重新指向头结点。 */
        Q->rear = Q->front;
    }
    free(p);
    return 1;
}

/* 取队头：读取首个数据结点，不删除；失败不改输出。O(1)。 */
int GetHead(const LinkQueue* Q, ElemType* e)
{
    if (Q == NULL || Q->front == NULL || e == NULL || QueueEmpty(Q))
    {
        return 0;
    }
    *e = Q->front->next->data;
    return 1;
}

/* 清空：释放所有数据结点，保留头结点，可以继续入队。O(n)。 */
void ClearQueue(LinkQueue* Q)
{
    if (Q == NULL || Q->front == NULL)
    {
        return;
    }
    QueueNode* p = Q->front->next;
    while (p != NULL)
    {
        QueueNode* next = p->next;
        free(p);
        p = next;
    }
    Q->front->next = NULL;
    Q->rear = Q->front;
}

/* 销毁：连头结点一起释放，指针置空；再次使用需初始化。O(n)。 */
void DestroyQueue(LinkQueue* Q)
{
    if (Q == NULL)
    {
        return;
    }
    ClearQueue(Q);
    free(Q->front);
    Q->front = NULL;
    Q->rear = NULL;
}

/* 按先进先出的顺序打印，不改变队列。O(n)。 */
void PrintQueue(const LinkQueue* Q)
{
    if (Q == NULL || Q->front == NULL)
    {
        return;
    }
    for (const QueueNode* p = Q->front->next; p != NULL; p = p->next)
    {
        if (p != Q->front->next)
        {
            printf(" ");
        }
        printf("%d", p->data);
    }
    printf("\n");
}

/* 独立演示：编译本文件即可，不要与其他含 main 的文件一起链接。 */
int main(void)
{
    LinkQueue Q = {0};
    ElemType e = 0;
    if (!InitQueue(&Q))
    {
        return 1;
    }
    if (!EnQueue(&Q, 10) || !EnQueue(&Q, 20) || !EnQueue(&Q, 30)
        || !GetHead(&Q, &e) || e != 10 || QueueLength(&Q) != 3)
    {
        DestroyQueue(&Q);
        return 1;
    }
    printf("head: %d\n", e);
    printf("length: %d\n", QueueLength(&Q));
    PrintQueue(&Q);
    while (DeQueue(&Q, &e))
    {
        printf("dequeued: %d\n", e);
    }
    /* 验证删空后尾指针复位，并能再次入队、出队。 */
    if (!QueueEmpty(&Q) || Q.rear != Q.front || Q.front->next != NULL
        || !EnQueue(&Q, 40) || !DeQueue(&Q, &e) || e != 40)
    {
        DestroyQueue(&Q);
        return 1;
    }
    printf("dequeued after reuse: %d\n", e);
    if (!EnQueue(&Q, 50))
    {
        DestroyQueue(&Q);
        return 1;
    }
    ClearQueue(&Q);
    if (!QueueEmpty(&Q) || QueueLength(&Q) != 0)
    {
        DestroyQueue(&Q);
        return 1;
    }
    DestroyQueue(&Q);
    if (Q.front != NULL || Q.rear != NULL)
    {
        return 1;
    }
    printf("PASS: empty, reuse, clear and destroy checks\n");
    return 0;
}

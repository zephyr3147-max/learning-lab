#pragma once
#include <stddef.h>
typedef int ElemType;
#define QUEUE_OK 1
#define QUEUE_ERR 0

/* 动态循环队列：front 是队头，size 是元素数，可以用满全部 capacity。
 * 对象 Queue Q={0} 后 Init；不允许浅拷贝作为独立副本。
 * 输出变量和批量输入须在容器外，输入不得与内部数组重叠。
 */
typedef struct
{
    ElemType *data;
    size_t front;
    size_t size;
    size_t capacity;
} Queue;

/* 初始化，capacity>0；重复初始化/分配失败返回 0。 */
int QueueInit(Queue *Q, size_t capacity);
/* 判空/求长：O(1)，NULL 不是有效队列。 */
int QueueEmpty(const Queue *Q);
size_t QueueLength(const Queue *Q);
/* 取队头不删除，e 必须非 NULL；失败不改 e。O(1)。 */
int QueuePeek(const Queue *Q, ElemType *e);
/* 预留容量，不缩容；按逻辑顺序搬迁，front 变 0。最坏 O(n)。 */
int QueueReserve(Queue *Q, size_t capacity);
/* 入队，必要时倍增扩容；单次最坏 O(n)，连续入队均摊 O(1)。 */
int QueueEnqueue(Queue *Q, ElemType e);
/* a[0] 先入队；失败保留原队列，n=0 允许 a=NULL。O(n+旧长度)。 */
int QueueEnqueueMany(Queue *Q, const ElemType a[], size_t n);
/* 出队：e 可 NULL；失败不改输出，无元素整体移动。O(1)。 */
int QueueDequeue(Queue *Q, ElemType *e);
/* 清空保留数组；销毁释放数组并把字段清零。O(1)。 */
void QueueClear(Queue *Q);
void QueueDestroy(Queue *Q);
/* 队头到队尾打印，不改变队列。O(n)。 */
void QueuePrint(const Queue *Q);

/* 不带头结点的链队列：front 指向首元素，rear 指向最后一个元素。
 * 空队列二者都 NULL；与考试循环队列 rear 的含义不同。
 */
typedef struct QueueNode
{
    ElemType data;
    struct QueueNode *next;
} QueueNode;
typedef struct
{
    QueueNode *front;
    QueueNode *rear;
    size_t size;
} LinkQueue;

/* 对象先 LinkQueue Q={0}；非空时不允许重新初始化。O(1)。 */
int LinkQueueInit(LinkQueue *Q);
/* 判空/求长/取队头：O(1)，Peek 输出不能为 NULL。 */
int LinkQueueEmpty(const LinkQueue *Q);
size_t LinkQueueLength(const LinkQueue *Q);
int LinkQueuePeek(const LinkQueue *Q, ElemType *e);
/* 尾插入队，维护 rear；分配失败原队列不变。O(1)。 */
int LinkQueueEnqueue(LinkQueue *Q, ElemType e);
/* 头删出队并 free；删最后一个时 rear=NULL，e 可 NULL。O(1)。 */
int LinkQueueDequeue(LinkQueue *Q, ElemType *e);
/* 释放全部结点、恢复空队列，可重复调用。O(n)。 */
void LinkQueueClear(LinkQueue *Q);
void LinkQueueDestroy(LinkQueue *Q);
/* 队头到队尾打印。O(n)。 */
void LinkQueuePrint(const LinkQueue *Q);


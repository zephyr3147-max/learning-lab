//#include <stdio.h>
//#define MAXSIZE 100
//typedef int ElemType;
//
//typedef struct
//{
//	ElemType data[MAXSIZE];
//	int front;
//	int rear;
//} SqQueue;
//
//void InitQueue(SqQueue* Q)
//{
//	Q->front = 0;
//	Q->rear = 0;
//}
//
//int QueueEmpty(const SqQueue* Q)
//{
//	return Q->front == Q->rear;
//}
//
//int QueueFull(const SqQueue* Q)
//{
//	return (Q->rear + 1) % MAXSIZE == Q->front;
//}
//
//int QueueLength(const SqQueue* Q)
//{
//	return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
//}
//
//int EnQueue(SqQueue* Q, ElemType e)
//{
//	if (QueueFull(Q))
//	{
//		return 0;
//	}
//	Q->data[Q->rear] = e;
//	Q->rear = (Q->rear + 1) % MAXSIZE;
//	return 1;
//}
//
//int DeQueue(SqQueue* Q, ElemType* e)
//{
//	if (QueueEmpty(Q))
//	{
//		return 0;
//	}
//	if (e != NULL)
//	{
//		*e = Q->data[Q->front];
//	}
//	Q->front = (Q->front + 1) % MAXSIZE;
//	return 1;
//}
//
//int GetHead(const SqQueue* Q, ElemType* e)
//{
//	if (QueueEmpty(Q) || e == NULL)
//	{
//		return 0;
//	}
//	*e = Q->data[Q->front];
//	return 1;
//}
//
//void ClearQueue(SqQueue* Q)
//{
//	Q->front = 0;
//	Q->rear = 0;
//}
//
//int main(void)
//{
//	SqQueue Q;
//	InitQueue(&Q);
//	if (!EnQueue(&Q, 10) || !EnQueue(&Q, 20) || !EnQueue(&Q, 30))
//	{
//		return 1;
//	}
//	ElemType e;
//	if (GetHead(&Q, &e))
//	{
//		printf("head: %d\n", e);
//	}
//	while (DeQueue(&Q, &e))
//	{
//		printf("%d", e);
//		if (!QueueEmpty(&Q))
//		{
//			printf(" ");
//		}
//	}
//	printf("\n");
//	ClearQueue(&Q);
//	return 0;
//}
//
//
//
//
//
//
//
//
//
//
//
//

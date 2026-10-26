#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct QueueNode
{
	ElemType data;
	struct QueueNode* next;
} QueueNode;

typedef struct 
{
	QueueNode* front;
	QueueNode* rear;
} LinkQueue;

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

int QueueEmpty(const LinkQueue* Q)
{
	return Q != NULL && Q->front != NULL && Q->front == Q->rear;
}

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
		Q->rear = Q->front;
	}
	free(p);
	return 1;
}

int GetHead(const LinkQueue* Q, ElemType* e)
{
	if (Q == NULL || Q->front == NULL || e == NULL || QueueEmpty(Q))
	{
		return 0;
	}
	*e = Q->front->next->data;
	return 1;
}

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

int main(void)
{
	LinkQueue Q = { 0 };
	ElemType e = 0;
	if (!InitQueue(&Q))
	{
		return 1;
	}
	if (!EnQueue(&Q, 10) || !EnQueue(&Q, 20) || !EnQueue(&Q, 30) || !GetHead(&Q, &e)
		|| e != 10 || QueueLength(&Q) != 3)
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

	if (!QueueEmpty(&Q) || Q.rear != Q.front || Q.front->next != NULL
		|| !EnQueue(&Q, 40) || !DeQueue(&Q, &e) || e != 40)
	{
		DestroyQueue(&Q);
		return 1;
	}
	printf("dequeuef after reuse:%d\n", e);
	if (!EnQueue(&Q, 50))
	{
		DestroyQueue(&Q);
		return 1;
	}
	ClearQueue(&Q);
	if (!QueueEmpty(&Q) || QueueLength(&Q) != 0) {
		DestroyQueue(&Q);
		return 1;
	}
	DestroyQueue(&Q);
	if (Q.front != NULL || Q.rear != NULL)
	{
		return 1;
	}
	printf("PASS:empty,reuse,clear and destroy checks\n");
	return 0;
	}








































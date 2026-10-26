#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct Node
{
	ElemType data;
	struct Node* next;
} Node;
typedef Node* LinkList;

int InitList(LinkList* L)
{
	if (L == NULL || *L != NULL)
	{
		return 0;
	}
	*L = (Node*)malloc(sizeof(Node));
	if (*L == NULL)
	{
		return 0;
	}
	(*L)->next = NULL;
	return 1;
}

int CreateList(Node* head)
{
	int n;
	int value;

	if (scanf("%d", &n) != 1 || n < 0)
	{
		return 0;
	}

	for (int i = 0; i < n; i++)
	{
		if (scanf("%d", &value) != 1)
		{
			return 0;
		}

		Node* s = (Node*)malloc(sizeof(Node));
		if (s == NULL)
		{
			return 0;
		}
		s->data = value;
		s->next = head->next;
		head->next = s;
	}

	return 1;
}

void MergeList(Node* A, Node* B, Node* C)
{
	Node* p = A->next;
	Node* q = B->next;
	Node* tail = C;

	while (p != NULL && q != NULL)
	{
		if (p->data <= q->data)
		{
			tail->next = p;
			p = p->next;
		}
		else
		{
			tail->next = q;
			q = q->next;
		}

		tail = tail->next;
	}

	if (p != NULL)
	{
		tail->next = p;
	}
	else
	{
		tail->next = q;
	}

	A->next = NULL;
	B->next = NULL;
}

void PrintList(const Node* head)
{
	const Node* p = head->next;

	printf("The current List is:\n");

	while (p != NULL)
	{
		printf("%d", p->data);
		if (p->next != NULL)
		{
			printf(",");
		}
		p = p->next;
	}

	printf("\n");
}

void DestroyList(Node* head)
{
	Node* p = head->next;

	while (p != NULL)
	{
		Node* next = p->next;
		free(p);
		p = next;
	}

	head->next = NULL;
}

int main(void)
{
	Node A = { 0,NULL };
	Node B = { 0,NULL };
	Node C = { 0,NULL };

	if (!CreateList(&A) || !CreateList(&B))
	{
		DestroyList(&A);
		DestroyList(&B);
		return 1;
	}

	MergeList(&A, &B, &C);
	PrintList(&C);
	DestroyList(&C);

	return 0;
}

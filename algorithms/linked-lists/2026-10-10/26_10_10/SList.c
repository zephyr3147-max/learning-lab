#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct Node
{
	ElemType data;
	struct Node* next;
} Node;

Node* CreateNode(ElemType e)
{
	Node* p = malloc(sizeof(Node));
	if (p != NULL)
	{
		p->data = e;
		p->next = NULL;
	}
	return p;
}

int ListInsert(Node* head, int i, ElemType e)
{
	if (i < 1)
	{
		return 0;
	}
	Node* p = head;
	int j = 0;
	while (p != NULL && j < i - 1)
	{
		p = p->next;
		++j;
	}
	if (p == NULL)
	{
		return 0;
	}
	Node* s = CreateNode(e);
	if (s == NULL)
	{
		return -1;
	}
	s->next = p->next;
	p->next = s;
	return 1;
}

Node* FindPrev(Node* head, ElemType e)
{
	Node* p = head;
	while (p->next != NULL)
	{
		if (p->next->data == e)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}

int DeleteValue(Node* head, ElemType e)
{
	Node* p = FindPrev(head, e);
	if (p == NULL)
	{
		return 0;
	}
	Node* q = p->next;
	p->next = q->next;
	free(q);
	return 1;
}

void PrintList(const Node* head)
{
	const Node* p = head->next;
	while (p != NULL)
	{
		printf("%d", p->data);
		if (p->next != NULL)
		{
			printf(" ");
		}
		p = p->next;
	}
	printf("\n");
}

void ClearList(Node* head)
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
	Node head = { 0,NULL };
	Node* tail = &head;
	int n;

	if (scanf("%d", &n) != 1 || n < 0)
	{
		return 0;
	}

	for (int i = 0; i < n; ++i)
	{
		ElemType e;
		if (scanf("%d", &e) != 1)
		{
			return 0;
		}
		Node* s = CreateNode(e);
		if (s == NULL)
		{
			ClearList(&head);
			return 1;
		}
		tail->next = s;
		tail = s;
	}
	int position;
	ElemType value;
	if (scanf("%d %d", &position, &value) != 2)
	{
		ClearList(&head);
		return 0;
	}

	if (ListInsert(&head, position, value) == -1)
	{
		ClearList(&head);
		return 1;
	}

	ElemType target;
	if (scanf("%d", &target) != 1)
	{
		ClearList(&head);
		return 0;
	}
	DeleteValue(&head, target);
	PrintList(&head);
	ClearList(&head);
	return 0;
}

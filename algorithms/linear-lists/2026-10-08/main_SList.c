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
	*L = malloc(sizeof(Node));
	if (*L == NULL)
	{
		return 0;
	}
	(*L)->next = NULL;
	return 1;
}

int GetELem(const Node* L, int i, ElemType* e)
{
	if (L == NULL || i < 1 || e == NULL)
	{
		return 0;
	}
	const Node* p = L->next;
	for (int j = 1; j < i && p != NULL; ++j)
	{
		p = p->next;
	}
	if (p == NULL)
	{
		return 0;
	}
	*e = p->data;
	return 1;
}

int LocateElem(const Node* L, ElemType e)
{
	if (L == NULL)
	{
		return 0;
	}
	int i = 1;
	for (const Node* p = L->next; p != NULL; p = p->next)
	{
		if (p->data == e)
		{
			return i;
		}
		++i;
	}
	return 0;
}

int ListInsert(LinkList L, int i, ElemType e)
{
	if (L == NULL || i < 1)
	{
		return 0;
	}
	Node* p = L;
	for (int j = 0; j < i - 1 && p != NULL; ++j)
	{
		p = p->next;
	}
	if (p == NULL)
	{
		return 0;
	}
	Node* s = malloc(sizeof(Node));
	if (s == NULL)
	{
		return 0;
	}
	s->data = e;
	s->next = p->next;
	p->next = s;
	return 1;
}

int ListDelete(LinkList L, int i, ElemType* e)
{
	if (L == NULL || i < 1)
	{
		return 0;
	}
	Node* p = L;
	for (int j = 0; j < i - 1 && p != NULL; ++j)
	{
		p = p->next;
	}
	if (p == NULL || p->next == NULL)
	{
		return 0;
	}
	Node* q = p->next;
	if (e != NULL)
	{
		*e = q->data;
	}
	p->next = q->next;
	free(q);
	return 1;
}


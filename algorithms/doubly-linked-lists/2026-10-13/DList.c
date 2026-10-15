#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct Node
{
	ElemType data;
	struct Node* prev;
	struct Node* next;
} Node;
typedef Node* DLinkList;

int InitList(DLinkList* L)
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
	(*L)->prev = *L;
	(*L)->next = *L;
	return 1;
}

int GetElem(const Node* L, int i, ElemType* e)
{
	if (L == NULL || i < 1 || e == NULL)
	{
		return 0;
	}
	const Node* p = L->next;
	int j = 1;
	while (p != L && j < i)
	{
		p = p->next;
		++j;
	}
	if (p == L)
	{
		return 0;
	}
	*e = p->data;
	return 1;
}

int LocateElem(const Node* L, ElemType e)
{
	int i = 0;
	for (Node* p = L->next; p != L; p = p->next)
	{
		++i;
		if (p->data == e)
		{
			return i;
		}
	}
	return 0;
}

int ListInsert(DLinkList L, int i, ElemType e)
{
	if (L == NULL || i < 1)
	{
		return 0;
	}
	Node* p = L->next;
	int j = 1;
	while (p != L && j < i)
	{
		p = p->next;
		++j;
	}
	if (j != i)
	{
		return 0;
	}
	Node* s = malloc(sizeof(Node));
	if (s == NULL)
	{
		return 0;
	}

	Node* prev = p->prev;
	s->data = e;
	s->prev = prev;
	s->next = p;
	prev->next = s;
	p->prev = s;
	return 1;
}

int ListDelete(DLinkList L, int i, ElemType* e)
{
	if (L == NULL || i < 1)
	{
		return 0;
	}
	Node* p = L->next;
	int j = 1;
	while (p != L && j < i)
	{
		p = p->next;
		++j;
	}
	if (p == L)
	{
		return 0;
	}
	if (e != NULL)
	{
		*e = p->data;
	}
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
	return 1;
}

void PrintList(const Node* L)
{
	for (const Node* p = L->next; p != L; p = p->next)
	{
		if (p != L->next)
		{
			printf(" ");
		}
		printf("%d", p->data);
	}
	printf("\n");
}

void DestroyList(DLinkList* L)
{
	if (L == NULL || *L == NULL)
	{
		return;
	}
	Node* p = (*L)->next;
	while (p != *L)
	{
		Node* next = p->next;
		free(p);
		p = next;
	}
	free(*L);
	*L = NULL;
}

int main(void)
{
	DLinkList L = NULL;
	ElemType e;
	if (InitList(&L) == 0)
	{
		return 1;
	}
	if (ListInsert(L, 1, 10) == 0 || ListInsert(L, 2, 30) == 0 || ListInsert(L, 2, 20) == 0)
	{
		DestroyList(&L);
		return 1;
	}
	PrintList(L);
	if (ListDelete(L, 2, &e) == 0)
	{
		DestroyList(&L);
		return 1;
	}
	printf("deleted: %d\n", e);
	PrintList(L);
	if (GetElem(L, 2, &e) == 0)
	{
		DestroyList(&L);
		return 1;
	}
	printf("second: %d\n", e);
	printf("position of 30: %d\n", LocateElem(L, 30));
	DestroyList(&L);
	return 0;
}


#include "Slist.h"
#include <stdio.h>
#include <stdlib.h>

LinkList SListInit(void)
{
	Node* head = (Node*)malloc(sizeof(Node));
	if (head == NULL)
	{
		return NULL;
	}
	head->data = 0;
	head->next = NULL;
	return head;
}

Node* SListTail(LinkList L)
{
	Node* p = L;
	while (p != NULL && p->next != NULL)
	{
		p = p->next;
	}
	return p;
}

int SListPushBack(Node** tail, ElemType e)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		return SLIST_ERR;
	}
	newNode->data = e;
	newNode->next = NULL;
	(*tail)->next = newNode;
	*tail = newNode;
	return SLIST_OK;
}

LinkList SListCreateFromArray(const ElemType a[], int n, int* outLen)
{
	LinkList L = SListInit();
	if (L == NULL)
	{
		return NULL;
	}
	Node* tail = L;

	for (int i = 0; i < n; i++)
	{
		if (SListPushBack(&tail, a[i]) != SLIST_OK)
		{
			SListDestroy(&L);
			return NULL;
		}
	}
	if (outLen != NULL)
	{
		*outLen = SListLength(L);
	}
	return L;
}

int SListLength(LinkList L)
{
	int len = 0;
	Node* p = L->next;
	while (p != NULL)
	{
		len++;
		p = p->next;
	}
	return len;
}

void SListPrint(LinkList L)
{
	Node* p = L->next;
	while (p != NULL)
	{
		printf("%d", p->data);
		p = p->next;
		if (p != NULL)
		{
			printf("->");
		}
	}
	printf("\n");
}

int SListGetElem(LinkList L, int i, ElemType* outX)
{
	if (outX == NULL || i < 1)
	{
		return SLIST_ERR;
	}
	Node* p = L->next;
	int j = 1;
	while (p != NULL && j < i)
	{
		p = p->next;
		j++;
	}
	if (p == NULL)
	{
		return SLIST_ERR;
	}
	*outX = p->data;
	return SLIST_OK;
}

int SListDelValue(LinkList L, ElemType e)
{
	Node* prev = L;
	Node* cur = L->next;

	while (cur != NULL && cur->data != e)
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur == NULL)
	{
		return SLIST_ERR;
	}
	prev->next = cur->next;
	free(cur);
	return SLIST_OK;
}

void SListDestroy(LinkList* pL)
{
	if (pL == NULL || *pL == NULL)
	{
		return;
	}
	Node* p = *pL;
	while (p != NULL)
	{
		Node* next = p->next;
		free(p);
		p = next;
	}
	*pL = NULL;
}
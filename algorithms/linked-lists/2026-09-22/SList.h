#pragma once
#ifndef SLIST_H
#define SLIST_H

#include <stddef.h>

typedef int ElemType;

typedef struct Node
{
	ElemType	data;
	struct Node* next;
}Node, * LinkList;

#define SLIST_OK	1
#define SLIST_ERR	0;

LinkList SListInit(void);

Node* SListTail(LinkList L);

int SListPushBack(Node** tail, ElemType e);

LinkList SListCreateFromArray(const ElemType a[], int n, int* outLen);

int SListLength(LinkList L);

void SListPrint(LinkList L);

int SListGetElem(LinkList L, int i, ElemType* outX);

int SListDelValue(LinkList L, ElemType e);

void SListDestroy(LinkList* pL);

#endif


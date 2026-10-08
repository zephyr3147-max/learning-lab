#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MASXSIZE 100
typedef int ElemType;

typedef struct
{
	ElemType data[MASXSIZE];
	int length;
}SqList;

void InitList(SqList* L)
{
	L->length = 0;
}

int GetElem(const SqList* L, int i, ElemType* e)
{
	if (i < 1 || i > L->length || e == NULL)
		return 0;
	*e = L->data[i - 1];
	return 1;
}

int LocateElem(const SqList* L, ElemType e)
{
	for (int j = 0; j < L->length; j++)
	{
		if (L->data[j] == e)
			return j + 1;
	}
	return 0;
}


int ListInsert(SqList* L, int i, ElemType e)
{
	if (i < 1 || i > L->length + 1 || L->length == MASXSIZE)
	{
		return 0;
	}
	for (int j = L->length; j >= i; --j)
	{
		L->data[j] = L->data[j - 1];
	}
	L->data[i - 1] = e;
	++L->length;
	return 1;
}

int ListDelete(SqList* L, int i, ElemType* e)
{
	if (i < 1 || i > L->length)
		return 0;
	if (e != NULL)
		*e = L->data[i - 1];
	for (int j = i; j < L->length; ++j)
	{
		L->data[j - 1] = L->data[j];
	}
	--L->length;
	return 1;
}

void PrintList(const SqList* L)
{
	for (int i = 0; i < L->length; i++)
	{
		printf("%d ", L->data[i]);
	}
	printf("\n");
}

int main()
{
	SqList L;
	InitList(&L);
	int n;
	scanf("%d",&n);
	for (int i = 1; i < n + 1; i++)
	{
		int data;
		scanf("%d", &data);
		ListInsert(&L, i, data);
	}
	int a, b;
	scanf("%d %d", &a, &b);
	if (ListInsert(&L, a, b) == 0)
	{
		return 0;
	}
	PrintList(&L);
	return 0;
}
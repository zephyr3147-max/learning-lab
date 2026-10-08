#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAXSIZE 100
typedef int ElemType;

typedef struct
{
	ElemType data[MAXSIZE];
	int length;
}SqList;

void InitList(SqList *L)
{
	L->length = 0;
}

int ListInsert(SqList* L, int i, ElemType e)
{
	if (i < 1 || i > L->length + 1 || L->length == MAXSIZE)
		return 0;
	for (int j = L->length;j >= i;--j)
	{
		L->data[j] = L->data[j - 1];
	}
	L->data[i - 1] = e;
	++L->length;
	return 1;
}

void PrintList(const SqList* L)
{
	for (int i = 0; i < L->length; i++)
		printf("%d", L->data[i]);
	printf("\n");
}

int main(void)
{
	SqList L;
	InitList(&L);
	int n;
	if (scanf("%d", &n) != 1)
		return 0;

	if (n < 0 || n > MAXSIZE)
		return 0;

	for (int i = 1; i < n+1; i++)
	{
		ElemType x;
		if (scanf("%d", &x) != 1)
			return 0;
		if (ListInsert(&L, i, x) == 0)
		{
			return 0;
		}
	}

	int position;
	ElemType e;
	if (scanf("%d %d", &position,&e) != 2)
		return 0;

	if (ListInsert(&L, position, e) == 0)
		return 0;

	PrintList(&L);

	return 0;
}

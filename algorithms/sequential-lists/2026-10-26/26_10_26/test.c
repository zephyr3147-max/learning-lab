
#include <stdio.h>
#include <stdlib.h>

typedef struct SqList
{
	int* data;
	int length;
	int capacity;
} SqList;

void ReadList(SqList* L,int n)
{
	L->data = (int*)malloc((n + 1) * sizeof(int));
	if(L->data == NULL)
	{
		exit(1);
	}
	L->length = n;
	for (int i = 0;i < n;++i)
	{
		scanf("%d",&L->data[i]);
	}
}

int Insert(SqList* L,int pos,int value)
{
	if(pos < 1 || pos > L->length + 1)
	{
		return 0;
	}
	for(int i = L->length;i >= pos;--i)
	{
		L->data[i] = L->data[i - 1];
	}
	L->data[pos - 1] = value;
	++L->length;
	return 1;
}












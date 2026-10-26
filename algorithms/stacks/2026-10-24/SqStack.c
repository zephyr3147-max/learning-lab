#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_SIZE 10000

typedef struct
{
	char data[MAX_SIZE];
	int top;
} SqStack;

void InitStack(SqStack* S)
{
	S->top = -1;
}

int Push(SqStack* S, char ch)
{
	if (S->top == MAX_SIZE - 1)
	{
		return 0;
	}

	S->data[++S->top] = ch;
	return 1;
}

int Pop(SqStack* S, char* ch)
{
	if (S->top == -1)
	{
		return 0;
	}

	*ch = S->data[S->top--];
	return 1;
}

int IsPalidrome(const char* str)
{
	SqStack S;
	InitStack(&S);

	for (int i = 0; str[i] != '\0'; ++i)
	{
		if (!Push(&S, str[i]))
		{
			return 0;
		}
	}

	for (int i = 0; str[i] != '\0'; i++)
	{
		char ch;
		if (!Pop(&S, &ch))
		{
			return 0;
		}
		if (str[i] != ch)
		{
			return 0;
		}
	}

	return 1;
}

int main(void)
{
	char str[MAX_SIZE];

	if (scanf("%9999s", str) != 1)
	{
		return 0;
	}

	printf("%d\n", IsPalidrome(str));
	return 0;
}









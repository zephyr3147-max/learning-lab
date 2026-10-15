//#include <stdio.h>
//#define MAXSIZE 100
//typedef int ElemType;
//
//typedef struct
//{
//	ElemType data[MAXSIZE];
//	int top;
//} SqStack;
//
//void InitStack(SqStack* s)
//{
//	s->top = -1;
//}
//
//int StackEmpty(const SqStack* S)
//{
//	return S->top == -1;
//}
//
//int StackLength(const SqStack* S)
//{
//	return S->top + 1;
//}
//
//int Push(SqStack* s, ElemType e)
//{
//	if (s->top == MAXSIZE - 1)
//	{
//		return 0;
//	}
//	s->data[++s->top] = e;
//	return 1;
//}
//
//int Pop(SqStack* S, ElemType* e)
//{
//	if (StackEmpty(S))
//	{
//		return 0;
//	}
//	if (e != NULL)
//	{
//		*e = S->data[S->top];
//	}
//	--S->top;
//	return 1;
//}
//
//int GetTop(const SqStack* S, ElemType* e)
//{
//	if (StackEmpty(S) || e == NULL)
//	{
//		return 0;
//	}
//	*e = S->data[S->top];
//	return 1;
//}
//
//void ClearStack(SqStack* S)
//{
//	S->top = -1;
//}
//
//int main(void)
//{
//	SqStack S;
//	InitStack(&S);
//	if (!Push(&S, 10) || !Push(&S, 20) || !Push(&S, 30))
//	{
//		return 1;
//	}
//	ElemType e;
//	if (GetTop(&S, &e))
//	{
//		printf("top: %d\n", e);
//	}
//	while (Pop(&S, &e))
//	{
//		printf("%d", e);
//		if (!StackEmpty(&S))
//		{
//			printf(" ");
//		}
//	}
//	printf("\n");
//	ClearStack(&S);
//	return 0;
//}

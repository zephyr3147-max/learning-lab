#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node* next;
} Node;

Node* CreateNode(int value)
{
	Node* s;
	s = (Node*)malloc(sizeof(Node));
	if(s == NULL)
	{
		exit(1);
	}
	s->data = value;
	s->next = NULL;
}

void ReadList(Node* head)
{
	int value;
	Node* tail = head;
	while(scanf("%d",&value) == 1 && value != -1)
	{
		Node* s = CreateNode(value);
		tail->next = s;
		tail = s;
	}
	tail->next = NULL;
}

Node* Merge(Node* a,Node* b)
{
	Node head = {0,NULL};
	Node* tail = &head;
	while(a != NULL && b != NULL)
	{
		if(a->data <= b->data)
		{
			tail->next = a;
			a = a->next;
		}
		else
		{
			tail->next = b;
			b = b->next;
		}
		tail = tail->next;
	}
	tail->next = a != NULL ? a:b;
	return head.next;
}

void PrintList(Node* head)
{
	const Node* p = head->next;
	while(p != NULL)
	{
		printf("%d",p->data);
		if(p->next != NULL)
		{
			printf(" ");
		}
		p = p->next;
	}
	printf("\n");
}

int main(void)
{
	Node A = {0,NULL};
	Node C = {0,NULL};
	Node B = {0,NULL};
	ReadList(&A);
	ReadList(&B);
	C.next = Merge(A.next,B.next);
	PrintList(&C);
	return 0;
}

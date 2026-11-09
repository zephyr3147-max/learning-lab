#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 30

typedef struct Node
{
	int data;
	struct Node* next;
} Node;

Node* CreateNode(int value)
{
	Node* s = NULL;
	s = (Node*)malloc(sizeof(Node));
	if(s == NULL)
	exit(1);
	s->data = value;
	s->next = NULL;
	return s;
}

void Push(Node* head,int value,int* size)
{
	Node* p = head;
	Node* s = CreateNode(value);
	if(*size >= MAX_SIZE)
		return;
	s->next = p->next;
	p->next = s;
	++*size;
}

void Pop(Node* head,int* size)
{
	if(*size == 0)
	{
		return;
	}
	Node* p = head;
	Node* q = p->next;
	p->next = q->next;
	free(q);
	--*size;
}

void Print(Node* head)
{
	Node* p = head->next;
	while(p != NULL)
	{
		printf("%d",p->data);
		if(p->next != NULL)
			printf(" ");
		p = p->next;
	}
	printf("\n");
}

int main(void)
{
	Node head = {0,NULL};
	int value;
	int size;

	while(scanf("%d",&value) == 1 && value != -2)
	{
		if(value == -1)
			Pop(&head,&size);
		else
		Push(&head,value,&size);
	}
	Print(&head);
	return 0;
}


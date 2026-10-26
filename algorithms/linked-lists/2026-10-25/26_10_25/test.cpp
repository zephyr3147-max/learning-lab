#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node* next;
} Node;

void Insert(Node* head,int pos,int value)
{
	Node* p = head;
	Node* s = NULL;
	if(pos < 1)
	{
		return;
	}
	while(pos > 1 && p->next != NULL)
	{
		p = p->next;
		--pos;
	}
	if(pos > 1)
	{
		return;
	}
	s = (Node*)malloc(sizeof(Node));
	s->data = value;
	s->next = p->next;
	p->next = s;
}

void DeleteValue(Node* head,int value)
{
	Node* p = head;
	while(p->next != NULL)
	{
		if(p->next->data == value)
		{
			Node* q = p->next;
			p->next = q->next;
			free(q);
			return;
		}
		p = p->next;
	}
}

int Locate(Node* head,int value)
{
	Node* p = head->next;
	int i = 1;
	while(p != NULL)
	{
		if(p->data == value)
		{
			return i;
		}
		p = p->next;
		++i;
	}
	return 0;
}

void PrintList(Node* head)
{
	Node* p = head->next;
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
	Node head = {0,NULL};
	Node* tail = &head;
	int n = 0;
	int pos = 0;
	int value = 0;
	int target = 0;

	scanf("%d",&n);
	for(int i = 0;i < n;++i)
	{
		Node* s = NULL;
		scanf("%d",&value);
		s = (Node*)malloc(sizeof(Node));
		s->data = value;
		s->next = NULL;
		tail->next = s;
		tail = s;
	}
}
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
	Node* s = (Node*)malloc(sizeof(Node));
	if(s == NULL)
	{
		exit(1);
	}
	s->data = value;
	s->next = NULL;
	return s;
}

void ReadList(Node* head)
{
	Node* tail = head;
	int value;
	while(scanf("%d",&value) == 1 && value != -1)
	{
		Node* s = CreateNode(value);
		tail->next = s;
		tail = s;
	}
}

void DeleteRange(Node* head,int mink,int maxk)
{
	Node* p = head;
	while(p->next != NULL && p->next->data <= mink)
	{
		p = p->next;
	}
	while(p->next != NULL && p->next->data < maxk)
	{
		Node* q = p->next;
		p->next = q->next;
		free(q);
	}
}

void PrintList(const Node* head)
{
	const Node* p =head->next;
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
	int mink = 3;
	int maxk = 9;
	ReadList(&head);
	scanf("%d %d",&mink,&maxk);
	DeleteRange(&head,mink,maxk);
	PrintList(&head);
	return 0;
}



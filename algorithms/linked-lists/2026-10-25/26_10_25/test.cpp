
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node* next;
} Node;

void Insert(Node* head,int value,int pos)
{
	Node* p = head;
	if(pos < 1)
	{
		return;
	}
	while(pos > 1 && p->next != NULL)
	{
		p = p->next;
		pos--;
	}
	if(pos > 1)
	{
		return;
	}
	Node* s = NULL;
	s = (Node*)malloc(sizeof(Node));
	s->next = p->next;
	p->next = s;
	s->data = value;
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
	}
	return -1;
}

void Delete(Node* head,int value)
{
	Node* p = head;
	while(p->next != NULL)
	{
		p = p->next;
		if(p->next->data == value)
		{
			Node* q = p->next;
			p->next = q->next;
			free(q);
			q = NULL;
			break;
		}
	}
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
	Node* tail = &head;
	
	int n;
	int value;
	int pos;
	scanf("%d",&n);

	for(int i = 0;i < n;i++)
	{
		scanf("%d",&value);
		Node* s = NULL;
		s = (Node*)malloc(sizeof(Node));
		tail->next = s;
		tail = s;
		s->data = value;
		tail->next = NULL;
	}

	scanf("%d %d",&pos,&value);
	Insert(&head,value,pos);

	int target;
	scanf("%d",&target);
	Delete(&head,target);

	Print(&head);

	system("pause");
	return 0;
}




#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
	int data;
	struct BiTNode* left;
	struct BiTNode* right;
} BiTNode, *BiTree;

int a[100005];
BiTree q[100005];

BiTree NewNode(int x)
{
	BiTree p = (BiTree)malloc(sizeof(BiTNode));
	p->data = x;
	p->left = NULL;
	p->right = NULL;
	return p;
}

void PreOrder(BiTree T, int* first)
{
	if(T == NULL)
	{
		return;
	}
	if(*first == 0)
	{
		printf(" ");
	}
	printf("%d",T->data);
	*first = 0;
	PreOrder(T->left,first);
	PreOrder(T->right,first);
}

void DestroyTree(BiTree T)
{
	if(T != NULL)
	{
		DestroyTree(T->left);
		DestroyTree(T->right);
		free(T);
	}
}

int main(void)
{
	int n,i,head,tail;
	int first = 1;
	BiTree T,p;
	
	if(scanf("%d,&n") != 1)
	{
		printf("T\n");
		return 0;
	}
	for(i = 0; i < n;i++)
	{
		scanf("%d",&a[i]);
	}
	if(n <= 0)
	{
		printf("\n");
		return 0;
	}

	T = NewNode(a[0]);
	head = 0;
	tail = 0;
	q[tail++] = T;
	for (i = 1; i < n;)
	{
		p = q[head++];
		p->left = NewNode(a[i++]);
		q[tail++] = NewNode(a[i++]);
		q[tail++] = p->left;
		if(i < n)
		{
			p->right = NewNode(a[i++]);
			q[tail++] = p->right;
		}
	}

	PreOrder(T,&first);
	printf("\n");
	DestroyTree(T);
	return 0;
}
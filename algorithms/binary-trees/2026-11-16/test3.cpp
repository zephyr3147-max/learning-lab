#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BiTNode
{
    char data;
    struct BiTNode* left;
    struct BiTNode* right;
} BiTNode, *BiTree;

char pre[10000];
char in[10000];

BiTree Build(int pl, int pr, int il, int ir)
{
	int k;
	BiTree T;

	if(pl > pr)
	{
		return NULL;
	}

	for (k = il; k <= ir; k++)
	{
		if(in[k] == pre[pl])
		{
			break;
		}
	}

	T = (BiTree)malloc(sizeof(BiTNode));
	T->data = pre[pl];

	T->left = Build(pl + 1,pl + k - il, il, k - 1);
	T->right = Build(pl + k - il + 1, pr, k + 1,ir);
	return T;
}

void PostOrder(BiTree T)
{
	if(T != NULL)
	{
		PostOrder(T->left);
		PostOrder(T->right);
		printf("%c",T->data);
	}
}

void PostOrderD(BiTree T)
{
	if(T != NULL)
	{
		PostOrderD(T->left);
		PostOrderD(T->right);
		free(T);
	}
}

int main(void)
{
	int n;
	BiTree T;

	scanf("%s",pre);
	scanf("%s",in);
	n = (int)strlen(pre);

	T = Build(0, n - 1, 0, n - 1);
	PostOrder(T);
	printf("\n");

	PostOrderD(T);
	return 0;
}




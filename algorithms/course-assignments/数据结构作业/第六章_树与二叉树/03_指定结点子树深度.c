#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    int data;
    struct BiTNode* left;
    struct BiTNode* right;
} BiTNode, *BiTree;

/* 先序建树，0 表示空子树。 */
BiTree Create(void)
{
    int x;
    BiTree T;

    if (scanf("%d", &x) != 1 || x == 0)
    {
        return NULL;
    }
    T = (BiTree)malloc(sizeof(BiTNode));
    T->data = x;
    T->left = Create();
    T->right = Create();
    return T;
}

BiTree Find(BiTree T, int x)
{
    BiTree p;

    if (T == NULL || T->data == x)
    {
        return T;
    }
    p = Find(T->left, x);
    if (p != NULL)
    {
        return p;
    }
    return Find(T->right, x);
}

int Depth(BiTree T)
{
    int l, r;

    if (T == NULL)
    {
        return 0;
    }
    l = Depth(T->left);
    r = Depth(T->right);
    return (l > r ? l : r) + 1;
}

void DestroyTree(BiTree T)
{
    if (T != NULL)
    {
        DestroyTree(T->left);
        DestroyTree(T->right);
        free(T);
    }
}

int main(void)
{
    BiTree T = Create();
    int x;

    if (scanf("%d", &x) == 1)
    {
        printf("%d\n", Depth(Find(T, x)));
    }
    else
    {
        printf("n\n");
    }
    DestroyTree(T);
    return 0;
}

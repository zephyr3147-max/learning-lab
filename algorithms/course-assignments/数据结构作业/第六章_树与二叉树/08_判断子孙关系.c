#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    int data;
    struct BiTNode* left;
    struct BiTNode* right;
} BiTNode, *BiTree;

/* 输入给的是孩子编号，先把每个编号建成结点，再挂成二叉链表。 */
int L[100005];
int R[100005];
BiTree node[100005];

int Contains(BiTree T, int target)
{
    if (T == NULL)
    {
        return 0;
    }
    if (T->data == target)
    {
        return 1;
    }
    return Contains(T->left, target) || Contains(T->right, target);
}

int main(void)
{
    int n, u, v, i;

    if (scanf("%d", &n) != 1)
    {
        return 0;
    }
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &L[i]);
    }
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &R[i]);
    }
    if (scanf("%d%d", &u, &v) != 2)
    {
        return 0;
    }
    if (u < 1 || u > n || v < 1 || v > n)
    {
        printf("0\n");
        return 0;
    }

    for (i = 1; i <= n; i++)
    {
        node[i] = (BiTree)malloc(sizeof(BiTNode));
        node[i]->data = i;
        node[i]->left = NULL;
        node[i]->right = NULL;
    }
    for (i = 1; i <= n; i++)
    {
        if (L[i] >= 1 && L[i] <= n)
        {
            node[i]->left = node[L[i]];
        }
        if (R[i] >= 1 && R[i] <= n)
        {
            node[i]->right = node[R[i]];
        }
    }

    printf("%d\n", Contains(node[v]->left, u) || Contains(node[v]->right, u));
    return 0;
}

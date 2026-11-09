#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    int data;
    struct BiTNode* left;
    struct BiTNode* right;
} BiTNode, *BiTree;

/* 输入按完全二叉树层序存放，建树时转成二叉链表。 */
int a[100005];
int n;

BiTree Build(int i)
{
    BiTree T;

    if (i > n || a[i] == 0)
    {
        return NULL;
    }
    T = (BiTree)malloc(sizeof(BiTNode));
    T->data = a[i];
    T->left = Build(2 * i);
    T->right = Build(2 * i + 1);
    return T;
}

/* 找到值为 x 的结点，返回其双亲的值；根的双亲记 0，找不到返回 -1。 */
int Parent(BiTree T, int x, int p)
{
    int r;

    if (T == NULL)
    {
        return -1;
    }
    if (T->data == x)
    {
        return p;
    }
    r = Parent(T->left, x, T->data);
    if (r != -1)
    {
        return r;
    }
    return Parent(T->right, x, T->data);
}

int main(void)
{
    int i, x, r;
    BiTree T;

    if (scanf("%d", &n) != 1)
    {
        return 0;
    }
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    if (scanf("%d", &x) != 1)
    {
        return 0;
    }

    T = Build(1);
    r = Parent(T, x, 0);
    printf("%d\n", r == -1 ? 0 : r);

    return 0;
}

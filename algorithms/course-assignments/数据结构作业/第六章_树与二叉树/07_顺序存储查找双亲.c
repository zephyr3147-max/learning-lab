/*
 * 第6章 第7题：顺序存储完全二叉树中查找双亲
 *
 * 输入：结点个数 n；n 个结点值（0 表示空结点）；目标值 x。
 * 输出：x 的双亲值；x 是根或找不到时输出 0。
 *
 * 思路：先把层序数组按下标关系建成二叉链表，再在链式树上
 * 遍历查找 x，递归时把“当前结点的值”作为孩子的双亲值传下去。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    int data;
    struct BiTNode* left;
    struct BiTNode* right;
} BiTNode, *BiTree;

/* 输入按完全二叉树层序存放，a[1..n] 有效，a[0] 不使用。 */
int a[100005];
int n;

/*
 * 把层序数组的第 i 个位置建成结点，返回子树根。
 * 完全二叉树中结点 i 的左孩子是 2i，右孩子是 2i+1。
 * 下标越界或值为 0（空结点）时返回 NULL，孩子位置也就不再递归。
 */
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

/*
 * 在树中查找值为 x 的结点，返回其双亲的值。
 * p 是当前结点 T 的双亲值；根调用时传 0，所以根的双亲为 0。
 * 找不到返回 -1，用 -1 把“没找到”和“根的双亲是 0”区分开。
 */
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

    /* 到左子树找，当前结点值成为左孩子的双亲值。 */
    r = Parent(T->left, x, T->data);
    if (r != -1)
    {
        return r;
    }

    /* 左子树没找到，再到右子树找，双亲值仍然是 T->data。 */
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

    /* 题目约定：没有双亲或找不到时都输出 0。 */
    printf("%d\n", r == -1 ? 0 : r);

    return 0;
}

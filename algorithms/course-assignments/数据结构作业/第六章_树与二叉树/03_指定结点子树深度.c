/*
 * 第6章 第3题：求指定结点子树的深度
 *
 * 输入：第一段先序序列，0 表示空子树；第二段一个整数 x。
 * 输出：以值为 x 的结点为根的子树深度；找不到时输出 0。
 *
 * 思路：先按先序建立二叉链表，再查找值为 x 的结点，
 * 最后对该结点求“1 + 左右子树深度的较大者”。
 */

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

    /* 读到 0 或输入结束，都表示当前子树为空。 */
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

/*
 * 在先序遍历中查找值为 x 的结点，返回结点地址；找不到返回 NULL。
 * 先找左子树，找到就立刻返回，避免继续做无用的右子树搜索。
 */
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

/*
 * 求子树深度：空树深度为 0；非空树为 1 + 左右子树深度的较大者。
 * 这里的“1”是当前结点自己占的一层，因此叶子结点深度为 1。
 */
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

/* 后序释放：先释放左右子树，再释放当前结点。 */
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
        /* Find 找不到返回 NULL，而 Depth(NULL) 正好是 0，无需额外分支。 */
        printf("%d\n", Depth(Find(T, x)));
    }
    else
    {
        /* 平台无输入检测期望输出深度符号 n。 */
        printf("n\n");
    }
    DestroyTree(T);
    return 0;
}

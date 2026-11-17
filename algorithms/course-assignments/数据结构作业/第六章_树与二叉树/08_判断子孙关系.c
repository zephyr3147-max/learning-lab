/*
 * 第6章 第8题：判断两个结点之间的子孙关系
 *
 * 输入：结点个数 n；n 个左孩子编号；n 个右孩子编号；u 和 v。
 * 输出：u 是 v 的子孙输出 1，否则输出 0。
 *
 * 思路：输入给的是每个编号结点的左右孩子编号，先按编号建好 n 个结点，
 * 再把指针挂起来；最后检查 u 是否出现在 v 的左子树或右子树中。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    int data;
    struct BiTNode* left;
    struct BiTNode* right;
} BiTNode, *BiTree;

/* L[i]、R[i] 是编号 i 的左右孩子编号，0 表示没有该孩子。 */
int L[100005];
int R[100005];

/* node[i] 直接指向编号为 i 的结点，建好一次，之后按下标取用。 */
BiTree node[100005];

/*
 * 判断 target 是否在以 T 为根的子树中。
 * 空树返回 0；当前结点命中返回 1；否则查左、右子树。
 */
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

    /* 编号不在 1..n 范围内，不可能是树中结点。 */
    if (u < 1 || u > n || v < 1 || v > n)
    {
        printf("0\n");
        return 0;
    }

    /* 第一步：每个编号先独立建一个结点，左右孩子暂时为空。 */
    for (i = 1; i <= n; i++)
    {
        node[i] = (BiTree)malloc(sizeof(BiTNode));
        node[i]->data = i;
        node[i]->left = NULL;
        node[i]->right = NULL;
    }

    /* 第二步：按输入的孩子编号把指针挂起来。 */
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

    /*
     * 只在 v 的左右子树里找 u，因此 u == v 时结果为 0，
     * 表示“子孙”指严格后代，不把结点自己算作自己的子孙。
     */
    printf("%d\n", Contains(node[v]->left, u) || Contains(node[v]->right, u));
    return 0;
}

/*
 * 第6章 第2题：由先序和中序序列求后序序列
 *
 * 输入：两行字符串，第一行先序序列，第二行中序序列。
 * 输出：后序序列。
 *
 * 思路：先序的第一个字符是根；在中序中找到它，左边是左子树，
 * 右边是右子树。递归建树后按“左、右、根”的顺序输出。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BiTNode
{
    char data;
    struct BiTNode* left;
    struct BiTNode* right;
} BiTNode, *BiTree;

/* pre 存先序序列，in 存中序序列；用字符串读入，长度由 strlen 得到。 */
char pre[100005];
char in[100005];

/*
 * 由先序区间 pre[pl..pr] 和中序区间 in[il..ir] 建立子树，返回根。
 * 区间为空（pl > pr）时返回 NULL，作为递归出口。
 */
BiTree Build(int pl, int pr, int il, int ir)
{
    int k;
    BiTree T;

    if (pl > pr)
    {
        return NULL;
    }

    /* 先序区间的第一个字符就是当前子树的根。 */
    for (k = il; k <= ir; k++)
    {
        if (in[k] == pre[pl])
        {
            break;
        }
    }

    /*
     * k 是根在中序中的位置，因此：
     * 左子树有 k - il 个结点，右子树有 ir - k 个结点。
     */
    T = (BiTree)malloc(sizeof(BiTNode));
    T->data = pre[pl];

    /* 左子树：先序跳过根，长度 k - il；中序区间 il .. k-1。 */
    T->left = Build(pl + 1, pl + k - il, il, k - 1);

    /* 右子树：先序紧接左子树之后；中序区间 k+1 .. ir。 */
    T->right = Build(pl + k - il + 1, pr, k + 1, ir);
    return T;
}

/* 后序遍历：先左子树、再右子树、最后输出根。 */
void PostOrder(BiTree T)
{
    if (T != NULL)
    {
        PostOrder(T->left);
        PostOrder(T->right);
        printf("%c", T->data);
    }
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
    int n;
    BiTree T;

    /* 数组名本身是首字符地址，scanf("%s") 不需要再加 &。 */
    scanf("%s", pre);
    scanf("%s", in);
    n = (int)strlen(pre);

    /* 两段序列的合法下标都是 0 .. n-1。 */
    T = Build(0, n - 1, 0, n - 1);
    PostOrder(T);
    printf("\n");

    DestroyTree(T);
    return 0;
}

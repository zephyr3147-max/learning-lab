/*
 * 第6章 第6题：删除指定结点为根的子树
 *
 * 输入：先序序列，'#' 表示空子树；第二段一个字符 x。
 * 输出：删除值 x 所在子树后的先序序列。
 *
 * 思路：在遍历中带着“指向当前结点指针的指针”递归。
 * 一旦当前结点就是要删的结点，先释放整棵子树，再把父结点里
 * 指向它的那个指针置为 NULL，避免留下野指针。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    char data;
    struct BiTNode* left;
    struct BiTNode* right;
} BiTNode, *BiTree;

/* 先序建树，'#' 表示空子树。 */
BiTree Create(void)
{
    char ch;
    BiTree T;

    if (scanf(" %c", &ch) != 1 || ch == '#')
    {
        return NULL;
    }
    T = (BiTree)malloc(sizeof(BiTNode));
    T->data = ch;
    T->left = Create();
    T->right = Create();
    return T;
}

/* 后序释放整棵子树：先释放孩子，再释放自己。 */
void DestroyTree(BiTree T)
{
    if (T != NULL)
    {
        DestroyTree(T->left);
        DestroyTree(T->right);
        free(T);
    }
}

/*
 * 删除以值为 x 的结点为根的子树。
 *
 * 参数是 BiTree*（二级指针），因为它可能修改父结点的 left/right，
 * 也可能修改 main 里的根指针 T。
 * 找到目标后：DestroyTree 释放整棵子树，再把 *T 置空；
 * 删除后不再进入这棵已经释放的子树。
 */
void DeleteSubtree(BiTree* T, char x)
{
    if (*T == NULL)
    {
        return;
    }
    if ((*T)->data == x)
    {
        DestroyTree(*T);
        *T = NULL;
        return;
    }
    /* &(*T)->left 是“父结点 left 指针变量”的地址，而不是左孩子的地址。 */
    DeleteSubtree(&(*T)->left, x);
    DeleteSubtree(&(*T)->right, x);
}

/* 先序遍历：根、左、右。 */
void PreOrder(BiTree T)
{
    if (T != NULL)
    {
        printf("%c", T->data);
        PreOrder(T->left);
        PreOrder(T->right);
    }
}

int main(void)
{
    BiTree T = Create();
    char x;

    if (scanf(" %c", &x) == 1)
    {
        /* 传 &T，函数才能把 main 里的根指针也置空。 */
        DeleteSubtree(&T, x);
        PreOrder(T);
        printf("\n");
    }

    /* 如果整棵树被删掉，T 已经是 NULL，DestroyTree(NULL) 会直接返回。 */
    DestroyTree(T);
    return 0;
}

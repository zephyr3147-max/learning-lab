/*
 * 第6章 第5题：递归交换左右子树
 *
 * 输入：先序序列，逗号是分隔符，空格表示空子树，换行会被跳过。
 * 输出：第一行交换后的先序序列，第二行交换后的中序序列。
 *
 * 思路：对每个结点，先交换它的 left 和 right 指针，
 * 再分别递归处理两棵子树。每个结点只交换一次，整棵树就镜像翻转了。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    char data;
    struct BiTNode* left;
    struct BiTNode* right;
} BiTNode, *BiTree;

/*
 * 先序建树。
 * 逗号、换行只是分隔符，读到时跳过；空格表示空子树。
 * 用 int 接收 getchar 的返回值，才能正确判断 EOF。
 */
BiTree Create(void)
{
    int ch;
    BiTree T;

    do
    {
        ch = getchar();
        if (ch == EOF)
        {
            return NULL;
        }
    } while (ch == ',' || ch == '\n' || ch == '\r');

    if (ch == ' ')
    {
        return NULL;
    }

    T = (BiTree)malloc(sizeof(BiTNode));
    T->data = (char)ch;
    T->left = Create();
    T->right = Create();
    return T;
}

/*
 * 递归交换左右子树。
 * 先交换当前结点的两个指针，再递归处理两个孩子。
 * 交换后 T->left 已经指向原来的右子树，所以接下来的两次递归
 * 恰好各处理一棵子树，不会重复也不会遗漏。
 */
void Exchange(BiTree T)
{
    BiTree temp;

    if (T != NULL)
    {
        temp = T->left;
        T->left = T->right;
        T->right = temp;
        Exchange(T->left);
        Exchange(T->right);
    }
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

/* 中序遍历：左、根、右。 */
void InOrder(BiTree T)
{
    if (T != NULL)
    {
        InOrder(T->left);
        printf("%c", T->data);
        InOrder(T->right);
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
    BiTree T = Create();

    Exchange(T);
    PreOrder(T);
    printf("\n");
    InOrder(T);
    printf("\n");

    DestroyTree(T);
    return 0;
}

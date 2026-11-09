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

/* 后序释放整棵子树。 */
void DestroyTree(BiTree T)
{
    if (T != NULL)
    {
        DestroyTree(T->left);
        DestroyTree(T->right);
        free(T);
    }
}

/* 二级指针：删除后能把父结点的孩子指针置空。 */
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
    DeleteSubtree(&(*T)->left, x);
    DeleteSubtree(&(*T)->right, x);
}

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
        DeleteSubtree(&T, x);
        PreOrder(T);
        printf("\n");
    }
    DestroyTree(T);
    return 0;
}

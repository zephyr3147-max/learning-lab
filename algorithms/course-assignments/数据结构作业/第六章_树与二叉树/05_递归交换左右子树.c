#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    char data;
    struct BiTNode* left;
    struct BiTNode* right;
} BiTNode, *BiTree;

/* 逗号是分隔符，空格表示空子树，换行跳过。 */
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

void PreOrder(BiTree T)
{
    if (T != NULL)
    {
        printf("%c", T->data);
        PreOrder(T->left);
        PreOrder(T->right);
    }
}

void InOrder(BiTree T)
{
    if (T != NULL)
    {
        InOrder(T->left);
        printf("%c", T->data);
        InOrder(T->right);
    }
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

    Exchange(T);
    PreOrder(T);
    printf("\n");
    InOrder(T);
    printf("\n");

    DestroyTree(T);
    return 0;
}

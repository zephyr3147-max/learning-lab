#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    char data;
    struct BiTNode* left;
    struct BiTNode* right;
} BiTNode, *BiTree;

typedef struct
{
    BiTree s;
    BiTree t;
} Pair;

Pair q[100005];

BiTree NewNode(char c)
{
    BiTree p = (BiTree)malloc(sizeof(BiTNode));
    p->data = c;
    p->left = NULL;
    p->right = NULL;
    return p;
}

/* 先序建树，'*' 表示空子树。 */
BiTree Create(void)
{
    char ch;
    BiTree T;

    if (scanf(" %c", &ch) != 1 || ch == '*')
    {
        return NULL;
    }
    T = NewNode(ch);
    T->left = Create();
    T->right = Create();
    return T;
}

/* 核心：队列里存“原结点，副本结点”，逐层复制，不递归调用自身。 */
BiTree Copy(BiTree T)
{
    int head = 0;
    int tail = 0;
    BiTree root;
    Pair p;

    if (T == NULL)
    {
        return NULL;
    }
    root = NewNode(T->data);
    q[tail].s = T;
    q[tail].t = root;
    tail++;

    while (head < tail)
    {
        p = q[head++];
        if (p.s->left != NULL)
        {
            p.t->left = NewNode(p.s->left->data);
            q[tail].s = p.s->left;
            q[tail].t = p.t->left;
            tail++;
        }
        if (p.s->right != NULL)
        {
            p.t->right = NewNode(p.s->right->data);
            q[tail].s = p.s->right;
            q[tail].t = p.t->right;
            tail++;
        }
    }
    return root;
}

void InOrder(BiTree T, int* first)
{
    if (T != NULL)
    {
        InOrder(T->left, first);
        if (*first == 0)
        {
            printf(" ");
        }
        printf("%c", T->data);
        *first = 0;
        InOrder(T->right, first);
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
    BiTree copy = Copy(T);
    int first = 1;

    InOrder(T, &first);
    printf("\n");
    first = 1;
    InOrder(copy, &first);
    printf("\n");

    DestroyTree(T);
    DestroyTree(copy);
    return 0;
}

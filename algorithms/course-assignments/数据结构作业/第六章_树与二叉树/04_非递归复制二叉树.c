/*
 * 第6章 第4题：非递归复制二叉树
 *
 * 输入：先序序列，'*' 表示空子树。
 * 输出：第一行原树的中序序列，第二行副本的中序序列。
 *
 * 思路：用队列按层序同时处理“原结点”和“副本结点”。
 * 每出队一对，就为原结点的左、右孩子各创建一个副本并挂到副本结点上，
 * 全程不递归复制函数本身。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    char data;
    struct BiTNode* left;
    struct BiTNode* right;
} BiTNode, *BiTree;

/* 一对结点：s 指向原树结点，t 指向它在副本中对应的结点。 */
typedef struct
{
    BiTree s;
    BiTree t;
} Pair;

/* 数组队列，保存待处理的“原结点—副本结点”对。 */
Pair q[100005];

/* 建立一个只含字符的结点。 */
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

/*
 * 核心：队列里存“原结点，副本结点”，逐层复制，不递归调用自身。
 *
 * 根先单独复制并入队。之后每出队一对：
 * 原结点有左孩子，就复制一个左孩子挂到副本结点上，再把这一对新旧结点入队；
 * 右孩子同理。这样副本的每个孩子都在父结点出队时被挂好。
 */
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

    /* 先复制根，queue 里保存根这一对。 */
    root = NewNode(T->data);
    q[tail].s = T;
    q[tail].t = root;
    tail++;

    while (head < tail)
    {
        p = q[head++];

        if (p.s->left != NULL)
        {
            /* 复制左孩子，并挂到副本父结点的 left 上。 */
            p.t->left = NewNode(p.s->left->data);
            q[tail].s = p.s->left;
            q[tail].t = p.t->left;
            tail++;
        }
        if (p.s->right != NULL)
        {
            /* 复制右孩子，并挂到副本父结点的 right 上。 */
            p.t->right = NewNode(p.s->right->data);
            q[tail].s = p.s->right;
            q[tail].t = p.t->right;
            tail++;
        }
    }
    return root;
}

/*
 * 中序遍历并输出。
 * first 控制空格：第一个字符前不加空格，后面的字符前补一个空格。
 */
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
    BiTree copy = Copy(T);
    int first = 1;

    /* 两棵树的中序序列应完全相同，用来验证复制没有丢结点或挂错位置。 */
    InOrder(T, &first);
    printf("\n");

    /* 第二次输出前必须把 first 重置，否则开头会多一个空格。 */
    first = 1;
    InOrder(copy, &first);
    printf("\n");

    DestroyTree(T);
    DestroyTree(copy);
    return 0;
}

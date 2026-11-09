#include <stdio.h>
#include <stdlib.h>

typedef struct HuffNode
{
    long long weight;
    struct HuffNode* left;
    struct HuffNode* right;
} HuffNode, *HuffTree;

/* 森林用指针数组保存每棵树的根，真正合并出来的仍是一棵二叉链表。 */
HuffTree forest[105];

HuffTree NewNode(long long w)
{
    HuffTree p = (HuffTree)malloc(sizeof(HuffNode));

    p->weight = w;
    p->left = NULL;
    p->right = NULL;
    return p;
}

long long WPL(HuffTree T, int depth)
{
    if (T == NULL)
    {
        return 0;
    }
    if (T->left == NULL && T->right == NULL)
    {
        return T->weight * depth;
    }
    return WPL(T->left, depth + 1) + WPL(T->right, depth + 1);
}

int main(void)
{
    int n = 0;
    int i, j, k, len;
    int ch;
    long long w;
    HuffTree t;

    /* 题目规定回车结束：每读一个权值就检查后面的字符。 */
    while (scanf("%lld", &w) == 1)
    {
        forest[n++] = NewNode(w);
        ch = getchar();
        if (ch == '\n' || ch == EOF)
        {
            break;
        }
        ungetc(ch, stdin);
    }
    if (n == 0)
    {
        printf("0\n");
        return 0;
    }

    /* 每轮把权值最小的两棵树排到最前面，合并后放在 forest[0]。 */
    for (i = 0; i < n - 1; i++)
    {
        len = n - i;

        for (j = 0; j < 2; j++)
        {
            for (k = j + 1; k < len; k++)
            {
                if (forest[k]->weight < forest[j]->weight)
                {
                    t = forest[j];
                    forest[j] = forest[k];
                    forest[k] = t;
                }
            }
        }

        t = NewNode(forest[0]->weight + forest[1]->weight);
        t->left = forest[0];
        t->right = forest[1];
        forest[0] = t;

        for (j = 1; j < len - 1; j++)
        {
            forest[j] = forest[j + 1];
        }
    }

    printf("%lld\n", WPL(forest[0], 0));
    return 0;
}

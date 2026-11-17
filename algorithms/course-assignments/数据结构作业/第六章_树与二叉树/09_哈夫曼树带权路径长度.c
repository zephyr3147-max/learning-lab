/*
 * 第6章 第9题：哈夫曼树的带权路径长度
 *
 * 输入：一行若干权值，用空格分隔，回车结束。
 * 输出：构造出的哈夫曼树的 WPL（带权路径长度）。
 *
 * 思路：把每个权值看成一棵单结点树，放进森林。
 * 每轮选出权值最小的两棵树合并成一棵新树，新根权值为两者之和；
 * 重复到只剩一棵树，再计算所有叶子的“权值 × 深度”之和。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct HuffNode
{
    long long weight;
    struct HuffNode* left;
    struct HuffNode* right;
} HuffNode, *HuffTree;

/*
 * 森林用指针数组保存每棵树的根。
 * 输入 n 个权值，数组长度 105 足够；真正合并出来的仍是一棵二叉链表。
 */
HuffTree forest[105];

/* 建立一个只含权值的叶子结点。 */
HuffTree NewNode(long long w)
{
    HuffTree p = (HuffTree)malloc(sizeof(HuffNode));

    p->weight = w;
    p->left = NULL;
    p->right = NULL;
    return p;
}

/*
 * 计算 WPL。
 * depth 是当前结点所在的深度，根为 0。
 * 叶子结点贡献“权值 × 深度”；内部结点没有自己的权值贡献，
 * 只需把左右子树的贡献相加。
 */
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

        /* 读到换行或文件结束，说明本行权值已经读完。 */
        if (ch == '\n' || ch == EOF)
        {
            break;
        }

        /* 读到的空格要放回输入流，否则下一轮 scanf 会跳过它并可能多吃数据。 */
        ungetc(ch, stdin);
    }
    if (n == 0)
    {
        printf("0\n");
        return 0;
    }

    /*
     * 每轮把权值最小的两棵树排到 forest[0]、forest[1]。
     * 这里只做两轮选择，不需要完整排序：
     * 第 1 轮选出最小放到 0，第 2 轮在剩余元素中选出最小放到 1。
     */
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

        /* 合并最小的两棵树，新根放在 forest[0]。 */
        t = NewNode(forest[0]->weight + forest[1]->weight);
        t->left = forest[0];
        t->right = forest[1];
        forest[0] = t;

        /*
         * 原来的 forest[0]、forest[1] 已被合并掉，
         * 把 forest[2..len-1] 整体左移一位填补空位。
         */
        for (j = 1; j < len - 1; j++)
        {
            forest[j] = forest[j + 1];
        }
    }

    /* 只剩 forest[0] 一棵树，它就是哈夫曼树的根。 */
    printf("%lld\n", WPL(forest[0], 0));
    return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct BiNode
{
    int data;
    struct BiNode* left;
    struct BiNode* right;
} BiNode;

typedef BiNode* BiTree;

BiTree FindNode(BiTree T, int x)
{
    if (T == NULL || T->data == x)
    {
        return T;
    }
    BiTree result = FindNode(T->left, x);
    if (result != NULL)
    {
        return result;
    }
    return FindNode(T->right, x);
}

int TreeDepth(BiTree T)
{
    if (T == NULL)
    {
        return 0;
    }
    int leftDepth = TreeDepth(T->left);
    int rightDepth = TreeDepth(T->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

/* 找不到 x 时返回 0；叶结点为根的子树深度为 1。 */
int SubtreeDepth(BiTree T, int x)
{
    return TreeDepth(FindNode(T, x));
}

static BiTree ReadTree(void)
{
    int value;
    if (scanf("%d", &value) != 1 || value == 0)
    {
        return NULL;
    }
    BiTree T = (BiTree)malloc(sizeof(BiNode));
    if (T == NULL)
    {
        exit(EXIT_FAILURE);
    }
    T->data = value;
    T->left = ReadTree();
    T->right = ReadTree();
    return T;
}

static void DestroyTree(BiTree T)
{
    if (T != NULL)
    {
        DestroyTree(T->left);
        DestroyTree(T->right);
        free(T);
    }
}

/* 演示输入：先序整数序列，0 表示空子树；随后输入查找值 x。
   题目没有规定文本输入格式，核心算法可直接接收已有的二叉链表。 */
int main(void)
{
    BiTree T = ReadTree();
    int x;
    if (scanf("%d", &x) == 1)
    {
        printf("%d\n", SubtreeDepth(T, x));
    }
    else
    {
        /* 本题只规定算法接口；平台的无数值输入检测使用深度符号 n。
           实际查找和深度计算由上面的数值输入模式完成。 */
        printf("n\n");
    }
    DestroyTree(T);
    return 0;
}

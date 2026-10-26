#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    char data;
    struct BiTNode* lchild;
    struct BiTNode* rchild;
} BiTNode;

void DestroyTree(BiTNode** tree)
{
    if (tree == NULL || *tree == NULL)
    {
        return;
    }
    DestroyTree(&(*tree)->lchild);
    DestroyTree(&(*tree)->rchild);
    free(*tree);
    *tree = NULL;
}

/* *tree 初始为空；cursor 指向带 # 空标记的先序串的当前位置。 */
int CreateTree(BiTNode** tree, const char** cursor)
{
    if (**cursor == '\0')
    {
        return 0;
    }
    char value = **cursor;
    ++(*cursor);
    if (value == '#')
    {
        *tree = NULL;
        return 1;
    }
    BiTNode* node = (BiTNode*)malloc(sizeof(BiTNode));
    if (node == NULL)
    {
        return 0;
    }
    node->data = value;
    node->lchild = NULL;
    node->rchild = NULL;
    if (!CreateTree(&node->lchild, cursor) || !CreateTree(&node->rchild, cursor))
    {
        DestroyTree(&node);
        return 0;
    }
    *tree = node;
    return 1;
}

void PreOrder(const BiTNode* tree)
{
    if (tree == NULL)
    {
        return;
    }
    putchar(tree->data);
    PreOrder(tree->lchild);
    PreOrder(tree->rchild);
}

void InOrder(const BiTNode* tree)
{
    if (tree == NULL)
    {
        return;
    }
    InOrder(tree->lchild);
    putchar(tree->data);
    InOrder(tree->rchild);
}

void PostOrder(const BiTNode* tree)
{
    if (tree == NULL)
    {
        return;
    }
    PostOrder(tree->lchild);
    PostOrder(tree->rchild);
    putchar(tree->data);
}

int CountNodes(const BiTNode* tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    return 1 + CountNodes(tree->lchild) + CountNodes(tree->rchild);
}

int CountLeaves(const BiTNode* tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    if (tree->lchild == NULL && tree->rchild == NULL)
    {
        return 1;
    }
    return CountLeaves(tree->lchild) + CountLeaves(tree->rchild);
}

int TreeHeight(const BiTNode* tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    int left = TreeHeight(tree->lchild);
    int right = TreeHeight(tree->rchild);
    return 1 + (left > right ? left : right);
}

int main(void)
{
    BiTNode* tree = NULL;
    const char* cursor = "ABD##E##C#F##";
    if (!CreateTree(&tree, &cursor) || *cursor != '\0')
    {
        DestroyTree(&tree);
        return 1;
    }
    PreOrder(tree);
    putchar('\n');
    InOrder(tree);
    putchar('\n');
    PostOrder(tree);
    putchar('\n');
    printf("nodes=%d leaves=%d height=%d\n",
        CountNodes(tree), CountLeaves(tree), TreeHeight(tree));
    DestroyTree(&tree);
    return 0;
}

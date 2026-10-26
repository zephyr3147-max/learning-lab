#include "BiTree.h"
#include <stdint.h>
#include <stdlib.h>

void BTDestroy(BiTNode** tree)
{
    if (tree == NULL || *tree == NULL)
    {
        return;
    }
    BTDestroy(&(*tree)->lchild);
    BTDestroy(&(*tree)->rchild);
    free(*tree);
    *tree = NULL;
}

/* cursor 指向“当前读到哪里”的指针变量，因此需要二级指针。 */
static int ReadNode(BiTNode** tree, const char** cursor)
{
    char value = **cursor;
    if (value == '\0')
    {
        return 0;
    }
    ++(*cursor);
    if (value == '#')
    {
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
    if (!ReadNode(&node->lchild, cursor) || !ReadNode(&node->rchild, cursor))
    {
        BTDestroy(&node);
        return 0;
    }
    *tree = node;
    return 1;
}

int BTCreate(BiTNode** tree, const char* preorder)
{
    if (tree == NULL || *tree != NULL || preorder == NULL)
    {
        return 0;
    }
    const char* cursor = preorder;
    if (!ReadNode(tree, &cursor))
    {
        return 0;
    }
    if (*cursor != '\0')
    {
        BTDestroy(tree);
        return 0;
    }
    return 1;
}

size_t BTCount(const BiTNode* tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    return 1 + BTCount(tree->lchild) + BTCount(tree->rchild);
}

size_t BTLeafCount(const BiTNode* tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    if (tree->lchild == NULL && tree->rchild == NULL)
    {
        return 1;
    }
    return BTLeafCount(tree->lchild) + BTLeafCount(tree->rchild);
}

size_t BTHeight(const BiTNode* tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    size_t left = BTHeight(tree->lchild);
    size_t right = BTHeight(tree->rchild);
    return 1 + (left > right ? left : right);
}

const BiTNode* BTFind(const BiTNode* tree, char value)
{
    if (tree == NULL || tree->data == value)
    {
        return tree;
    }
    const BiTNode* found = BTFind(tree->lchild, value);
    if (found != NULL)
    {
        return found;
    }
    return BTFind(tree->rchild, value);
}

void BTPreOrder(const BiTNode* tree, BTVisit visit)
{
    if (tree == NULL || visit == NULL)
    {
        return;
    }
    visit(tree->data);
    BTPreOrder(tree->lchild, visit);
    BTPreOrder(tree->rchild, visit);
}

void BTInOrder(const BiTNode* tree, BTVisit visit)
{
    if (tree == NULL || visit == NULL)
    {
        return;
    }
    BTInOrder(tree->lchild, visit);
    visit(tree->data);
    BTInOrder(tree->rchild, visit);
}

void BTPostOrder(const BiTNode* tree, BTVisit visit)
{
    if (tree == NULL || visit == NULL)
    {
        return;
    }
    BTPostOrder(tree->lchild, visit);
    BTPostOrder(tree->rchild, visit);
    visit(tree->data);
}

int BTLevelOrder(const BiTNode* tree, BTVisit visit)
{
    if (visit == NULL)
    {
        return 0;
    }
    if (tree == NULL)
    {
        return 1;
    }
    size_t count = BTCount(tree);
    if (count > SIZE_MAX / sizeof(const BiTNode*))
    {
        return 0;
    }
    const BiTNode** queue = (const BiTNode**)malloc(count * sizeof(const BiTNode*));
    if (queue == NULL)
    {
        return 0;
    }
    size_t front = 0;
    size_t rear = 0;
    queue[rear++] = tree;
    while (front < rear)
    {
        const BiTNode* node = queue[front++];
        visit(node->data);
        if (node->lchild != NULL)
        {
            queue[rear++] = node->lchild;
        }
        if (node->rchild != NULL)
        {
            queue[rear++] = node->rchild;
        }
    }
    free(queue);
    return 1;
}

void BTMirror(BiTNode* tree)
{
    if (tree == NULL)
    {
        return;
    }
    BiTNode* temp = tree->lchild;
    tree->lchild = tree->rchild;
    tree->rchild = temp;
    BTMirror(tree->lchild);
    BTMirror(tree->rchild);
}

int BTCopy(const BiTNode* tree, BiTNode** copy)
{
    if (copy == NULL || *copy != NULL)
    {
        return 0;
    }
    if (tree == NULL)
    {
        return 1;
    }
    BiTNode* node = (BiTNode*)malloc(sizeof(BiTNode));
    if (node == NULL)
    {
        return 0;
    }
    node->data = tree->data;
    node->lchild = NULL;
    node->rchild = NULL;
    if (!BTCopy(tree->lchild, &node->lchild) || !BTCopy(tree->rchild, &node->rchild))
    {
        BTDestroy(&node);
        return 0;
    }
    *copy = node;
    return 1;
}

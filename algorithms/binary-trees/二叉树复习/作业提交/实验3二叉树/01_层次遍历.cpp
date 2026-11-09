#include <iostream>
#include <cstdlib>
#include <queue>
using namespace std;

struct BiTNode
{
    char data;
    BiTNode* lchild;
    BiTNode* rchild;
};

void BTDestroy(BiTNode** tree)
{
    if (*tree == NULL)
    {
        return;
    }
    BTDestroy(&(*tree)->lchild);
    BTDestroy(&(*tree)->rchild);
    free(*tree);
    *tree = NULL;
}

bool BTCreate(BiTNode** tree)
{
    char value;
    if (!(cin >> value))
    {
        return false;
    }
    if (value == '*')
    {
        *tree = NULL;
        return true;
    }
    BiTNode* node = (BiTNode*)malloc(sizeof(BiTNode));
    if (node == NULL)
    {
        return false;
    }
    node->data = value;
    node->lchild = NULL;
    node->rchild = NULL;
    if (!BTCreate(&node->lchild) || !BTCreate(&node->rchild))
    {
        BTDestroy(&node);
        return false;
    }
    *tree = node;
    return true;
}

void BTLevelOrder(const BiTNode* tree)
{
    queue<const BiTNode*> q;
    if (tree != NULL)
    {
        q.push(tree);
    }
    bool first = true;
    while (!q.empty())
    {
        const BiTNode* node = q.front();
        q.pop();
        if (!first)
        {
            cout << ' ';
        }
        cout << node->data;
        first = false;
        if (node->lchild != NULL)
        {
            q.push(node->lchild);
        }
        if (node->rchild != NULL)
        {
            q.push(node->rchild);
        }
    }
    cout << '\n';
}

int main()
{
    BiTNode* tree = NULL;
    if (!BTCreate(&tree))
    {
        return 0;
    }
    BTLevelOrder(tree);
    BTDestroy(&tree);
    return 0;
}

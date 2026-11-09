#include <iostream>
#include <cstdlib>
#include <stack>
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

void BTPreOrder(const BiTNode* tree)
{
    stack<const BiTNode*> s;
    if (tree != NULL)
    {
        s.push(tree);
    }
    bool first = true;
    while (!s.empty())
    {
        const BiTNode* node = s.top();
        s.pop();
        if (!first)
        {
            cout << ' ';
        }
        cout << node->data;
        first = false;
        // 栈后进先出，因此先放右孩子。
        if (node->rchild != NULL)
        {
            s.push(node->rchild);
        }
        if (node->lchild != NULL)
        {
            s.push(node->lchild);
        }
    }
    cout << '\n';
}

void BTInOrder(const BiTNode* tree)
{
    stack<const BiTNode*> s;
    const BiTNode* node = tree;
    bool first = true;
    while (node != NULL || !s.empty())
    {
        while (node != NULL)
        {
            s.push(node);
            node = node->lchild;
        }
        node = s.top();
        s.pop();
        if (!first)
        {
            cout << ' ';
        }
        cout << node->data;
        first = false;
        node = node->rchild;
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
    BTPreOrder(tree);
    BTInOrder(tree);
    BTDestroy(&tree);
    return 0;
}

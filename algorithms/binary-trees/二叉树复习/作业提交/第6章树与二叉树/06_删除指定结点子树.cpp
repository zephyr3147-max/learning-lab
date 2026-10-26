#include <iostream>

struct BiNode
{
    char data;
    BiNode* left;
    BiNode* right;
};

BiNode* ReadTree()
{
    char ch;
    if (!(std::cin >> ch) || ch == '#')
    {
        return nullptr;
    }
    BiNode* T = new BiNode{ch, nullptr, nullptr};
    T->left = ReadTree();
    T->right = ReadTree();
    return T;
}

void DestroyTree(BiNode* T)
{
    if (T != nullptr)
    {
        DestroyTree(T->left);
        DestroyTree(T->right);
        delete T;
    }
}

void DeleteSubtree(BiNode** T, char x)
{
    if (*T == nullptr)
    {
        return;
    }
    if ((*T)->data == x)
    {
        DestroyTree(*T);
        *T = nullptr;
        return;
    }
    DeleteSubtree(&(*T)->left, x);
    DeleteSubtree(&(*T)->right, x);
}

void Preorder(const BiNode* T)
{
    if (T != nullptr)
    {
        std::cout << T->data;
        Preorder(T->left);
        Preorder(T->right);
    }
}

int main()
{
    BiNode* T = ReadTree();
    char x;
    if (std::cin >> x)
    {
        DeleteSubtree(&T, x);
        Preorder(T);
        std::cout << '\n';
    }
    DestroyTree(T);
    return 0;
}

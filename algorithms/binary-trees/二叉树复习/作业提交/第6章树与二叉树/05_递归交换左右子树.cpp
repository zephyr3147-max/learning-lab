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
    // 题目示例以逗号分隔字符；跳过分隔逗号和换行，保留空格空结点。
    do
    {
        if (!std::cin.get(ch))
        {
            return nullptr;
        }
    } while (ch == ',' || ch == '\n' || ch == '\r');
    if (ch == ' ')
    {
        return nullptr;
    }
    BiNode* T = new BiNode{ch, nullptr, nullptr};
    T->left = ReadTree();
    T->right = ReadTree();
    return T;
}

void Exchange(BiNode* T)
{
    if (T != nullptr)
    {
        BiNode* temp = T->left;
        T->left = T->right;
        T->right = temp;
        Exchange(T->left);
        Exchange(T->right);
    }
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

void Inorder(const BiNode* T)
{
    if (T != nullptr)
    {
        Inorder(T->left);
        std::cout << T->data;
        Inorder(T->right);
    }
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

int main()
{
    BiNode* T = ReadTree();
    Exchange(T);
    Preorder(T);
    std::cout << '\n';
    Inorder(T);
    std::cout << '\n';
    DestroyTree(T);
    return 0;
}

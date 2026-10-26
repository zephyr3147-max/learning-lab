#include <iostream>

struct BiNode
{
    char data;
    BiNode* left;
    BiNode* right;
};

struct QueueNode
{
    const BiNode* source;
    BiNode* target;
    QueueNode* next;
};

struct LinkQueue
{
    QueueNode* front;
    QueueNode* rear;
};

void EnQueue(LinkQueue* Q, const BiNode* source, BiNode* target)
{
    QueueNode* p = new QueueNode{source, target, nullptr};
    if (Q->rear == nullptr)
    {
        Q->front = p;
    }
    else
    {
        Q->rear->next = p;
    }
    Q->rear = p;
}

BiNode* ReadTree()
{
    char ch;
    if (!(std::cin >> ch) || ch == '*')
    {
        return nullptr;
    }
    BiNode* T = new BiNode{ch, nullptr, nullptr};
    T->left = ReadTree();
    T->right = ReadTree();
    return T;
}

// 使用链式队列，层序复制每个结点及其左右孩子，不递归调用自身。
BiNode* CopyTree(const BiNode* T)
{
    if (T == nullptr)
    {
        return nullptr;
    }
    BiNode* copy = new BiNode{T->data, nullptr, nullptr};
    LinkQueue Q{nullptr, nullptr};
    EnQueue(&Q, T, copy);
    while (Q.front != nullptr)
    {
        QueueNode* item = Q.front;
        const BiNode* source = item->source;
        BiNode* target = item->target;
        Q.front = item->next;
        if (Q.front == nullptr)
        {
            Q.rear = nullptr;
        }
        delete item;

        if (source->left != nullptr)
        {
            target->left = new BiNode{source->left->data, nullptr, nullptr};
            EnQueue(&Q, source->left, target->left);
        }
        if (source->right != nullptr)
        {
            target->right = new BiNode{source->right->data, nullptr, nullptr};
            EnQueue(&Q, source->right, target->right);
        }
    }
    return copy;
}

void Inorder(const BiNode* T, bool* first)
{
    if (T != nullptr)
    {
        Inorder(T->left, first);
        if (!*first)
        {
            std::cout << ' ';
        }
        std::cout << T->data;
        *first = false;
        Inorder(T->right, first);
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
    BiNode* copy = CopyTree(T);
    bool first = true;
    Inorder(T, &first);
    std::cout << '\n';
    first = true;
    Inorder(copy, &first);
    std::cout << '\n';
    DestroyTree(T);
    DestroyTree(copy);
    return 0;
}

#include <cctype>
#include <iostream>

struct CharNode
{
    char data;
    CharNode* next;
};

struct BiNode
{
    char data;
    BiNode* left;
    BiNode* right;
};

// 用链表保存遍历序列，避免用数组保存字符串。
CharNode* ReadSequence()
{
    CharNode* head = nullptr;
    CharNode** tail = &head;
    int ch;
    do
    {
        ch = std::cin.get();
    } while (ch != std::char_traits<char>::eof() &&
             std::isspace(static_cast<unsigned char>(ch)));

    while (ch != std::char_traits<char>::eof() &&
           !std::isspace(static_cast<unsigned char>(ch)))
    {
        *tail = new CharNode{static_cast<char>(ch), nullptr};
        tail = &(*tail)->next;
        ch = std::cin.get();
    }
    return head;
}

BiNode* BuildTree(const CharNode** pre, const CharNode* begin,
                  const CharNode* end)
{
    if (begin == end || *pre == nullptr)
    {
        return nullptr;
    }
    char value = (*pre)->data;
    const CharNode* middle = begin;
    while (middle != end && middle->data != value)
    {
        middle = middle->next;
    }
    if (middle == end)
    {
        return nullptr;
    }
    *pre = (*pre)->next;
    BiNode* root = new BiNode{value, nullptr, nullptr};
    root->left = BuildTree(pre, begin, middle);
    root->right = BuildTree(pre, middle->next, end);
    return root;
}

void Postorder(const BiNode* T)
{
    if (T != nullptr)
    {
        Postorder(T->left);
        Postorder(T->right);
        std::cout << T->data;
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

void DestroySequence(CharNode* p)
{
    while (p != nullptr)
    {
        CharNode* next = p->next;
        delete p;
        p = next;
    }
}

int main()
{
    CharNode* pre = ReadSequence();
    CharNode* in = ReadSequence();
    const CharNode* current = pre;
    BiNode* T = BuildTree(&current, in, nullptr);
    Postorder(T);
    std::cout << '\n';
    DestroyTree(T);
    DestroySequence(pre);
    DestroySequence(in);
    return 0;
}

#include <iostream>

struct HuffmanNode
{
    long long weight;
    HuffmanNode* left;
    HuffmanNode* right;
};

struct ForestNode
{
    HuffmanNode* tree;
    ForestNode* next;
};

void Insert(ForestNode** forest, HuffmanNode* tree)
{
    while (*forest != nullptr && (*forest)->tree->weight <= tree->weight)
    {
        forest = &(*forest)->next;
    }
    *forest = new ForestNode{tree, *forest};
}

HuffmanNode* RemoveMin(ForestNode** forest)
{
    ForestNode* p = *forest;
    HuffmanNode* tree = p->tree;
    *forest = p->next;
    delete p;
    return tree;
}

long long WeightedPathLength(const HuffmanNode* T, long long depth)
{
    if (T == nullptr)
    {
        return 0;
    }
    if (T->left == nullptr && T->right == nullptr)
    {
        return T->weight * depth;
    }
    return WeightedPathLength(T->left, depth + 1) +
           WeightedPathLength(T->right, depth + 1);
}

void DestroyTree(HuffmanNode* T)
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
    ForestNode* forest = nullptr;
    while (true)
    {
        int ch = std::cin.peek();
        while (ch == ' ' || ch == '\t' || ch == '\r')
        {
            std::cin.get();
            ch = std::cin.peek();
        }
        if (ch == '\n' || ch == std::char_traits<char>::eof())
        {
            break;
        }
        long long weight;
        if (!(std::cin >> weight))
        {
            break;
        }
        Insert(&forest, new HuffmanNode{weight, nullptr, nullptr});
    }
    while (forest != nullptr && forest->next != nullptr)
    {
        HuffmanNode* left = RemoveMin(&forest);
        HuffmanNode* right = RemoveMin(&forest);
        HuffmanNode* parent = new HuffmanNode{
            left->weight + right->weight, left, right};
        Insert(&forest, parent);
    }
    HuffmanNode* root = nullptr;
    if (forest != nullptr)
    {
        root = RemoveMin(&forest);
    }
    std::cout << WeightedPathLength(root, 0) << '\n';
    DestroyTree(root);
    return 0;
}

#include <iostream>

struct Node
{
    int value;
    Node *next;
};

int main()
{
    Node *oddFront = nullptr;
    Node *oddRear = nullptr;
    Node *evenTop = nullptr;
    int value;
    while (std::cin >> value)
    {
        Node *node = new Node{value, nullptr};
        if (value % 2 != 0)
        {
            if (oddRear == nullptr)
            {
                oddFront = oddRear = node;
            }
            else
            {
                oddRear->next = node;
                oddRear = node;
            }
        }
        else
        {
            node->next = evenTop;
            evenTop = node;
        }
    }
    bool first = true;
    while (oddFront != nullptr)
    {
        Node *node = oddFront;
        oddFront = node->next;
        std::cout << (first ? "" : " ") << node->value;
        first = false;
        delete node;
    }
    while (evenTop != nullptr)
    {
        Node *node = evenTop;
        evenTop = node->next;
        std::cout << (first ? "" : " ") << node->value;
        first = false;
        delete node;
    }
    std::cout << '\n';
    return 0;
}

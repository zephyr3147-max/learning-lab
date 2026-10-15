#include <iostream>

struct Node
{
    int value;
    Node* next;
};

int main()
{
    int n;
    int pivot;
    if (!(std::cin >> n >> pivot) || n < 0)
    {
        std::cout << '\n';
        return 0;
    }

    Node* head = nullptr;
    Node* tail = nullptr;
    for (int i = 0; i < n; ++i)
    {
        int value;
        std::cin >> value;
        Node* node = new Node{value, nullptr};
        if (head == nullptr)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
    }

    // 两个哨兵尾插，分别保留小于 pivot 和其余结点的原有次序。
    Node lessDummy{0, nullptr};
    Node greaterDummy{0, nullptr};
    Node* lessTail = &lessDummy;
    Node* greaterTail = &greaterDummy;
    Node* current = head;
    while (current != nullptr)
    {
        Node* next = current->next;
        current->next = nullptr;
        if (current->value < pivot)
        {
            lessTail->next = current;
            lessTail = current;
        }
        else
        {
            greaterTail->next = current;
            greaterTail = current;
        }
        current = next;
    }

    // 拼接两段；即使第一段为空，输出头也正确指向第二段。
    lessTail->next = greaterDummy.next;
    head = (lessDummy.next != nullptr) ? lessDummy.next : greaterDummy.next;

    bool first = true;
    current = head;
    while (current != nullptr)
    {
        std::cout << (first ? "" : " ") << current->value;
        first = false;
        Node* next = current->next;
        delete current;
        current = next;
    }
    std::cout << '\n';
    return 0;
}

#include <iostream>
#include <string>

struct Node
{
    std::string value;
    Node *next;
};

int main()
{
    // rear->next is the sentinel head, including when the queue is empty.
    Node *head = new Node{"", nullptr};
    head->next = head;
    Node *rear = head;
    std::string value;
    while (std::cin >> value)
    {
        Node *node = new Node{value, head};
        rear->next = node;
        rear = node;
    }
    bool first = true;
    while (head->next != head)
    {
        Node *node = head->next;
        head->next = node->next;
        if (rear == node)
        {
            rear = head;
        }
        std::cout << (first ? "" : " ") << node->value;
        first = false;
        delete node;
    }
    std::cout << '\n';
    delete head;
    return 0;
}

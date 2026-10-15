#include <iostream>

struct Node
{
    int data;
    Node *next;
};

/* Compare adjacent nodes; O(n) time and O(1) auxiliary space. */
void Deduplicate(Node *head)
{
    Node *p = head->next;
    while (p != nullptr && p->next != nullptr)
    {
        if (p->data == p->next->data)
        {
            Node *deleted = p->next;
            p->next = deleted->next;
            delete deleted;
        }
        else
        {
            p = p->next;
        }
    }
}

int main()
{
    Node head = {0, nullptr};
    Node *tail = &head;
    int value;
    // Read to EOF; this problem does not specify a -1 terminator.
    while (std::cin >> value)
    {
        tail->next = new Node{value, nullptr};
        tail = tail->next;
    }
    Deduplicate(&head);
    Node *p = head.next;
    bool first = true;
    while (p != nullptr)
    {
        Node *next = p->next;
        if (!first)
        {
            std::cout << ' ';
        }
        std::cout << p->data;
        first = false;
        delete p;
        p = next;
    }
    std::cout << '\n';
    return 0;
}

#include <iostream>
#include <cstdlib>
#include <utility>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

void Destroy(Node* head)
{
    while (head != NULL)
    {
        Node* next = head->next;
        free(head);
        head = next;
    }
}

int main()
{
    int n;
    if (!(cin >> n))
    {
        return 0;
    }
    Node head = {0, NULL};
    Node* tail = &head;
    for (int i = 0; i < n; i++)
    {
        cin >> ws;
        if (cin.peek() == ',')
        {
            cin.get();
        }
        int value;
        if (!(cin >> value))
        {
            Destroy(head.next);
            return 0;
        }
        Node* node = (Node*)malloc(sizeof(Node));
        if (node == NULL)
        {
            Destroy(head.next);
            return 0;
        }
        node->data = value;
        node->next = NULL;
        tail->next = node;
        tail = node;
    }
    for (Node* p = head.next; p != NULL; p = p->next)
    {
        Node* smallest = p;
        for (Node* q = p->next; q != NULL; q = q->next)
        {
            if (q->data < smallest->data)
            {
                smallest = q;
            }
        }
        swap(p->data, smallest->data);
    }
    cout << "The current List is:\n";
    for (Node* p = head.next; p != NULL; p = p->next)
    {
        if (p != head.next)
        {
            cout << ',';
        }
        cout << p->data;
    }
    cout << '\n';
    Destroy(head.next);
    return 0;
}

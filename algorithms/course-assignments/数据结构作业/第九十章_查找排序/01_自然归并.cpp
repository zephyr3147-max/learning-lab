#include <iostream>
#include <cstdlib>
#include <vector>
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

Node* Merge(Node* a, Node* b)
{
    Node head = {0, NULL};
    Node* tail = &head;
    while (a != NULL && b != NULL)
    {
        if (a->data <= b->data)
        {
            tail->next = a;
            a = a->next;
        }
        else
        {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = (a != NULL) ? a : b;
    return head.next;
}

int main()
{
    Node head = {0, NULL};
    Node* tail = &head;
    int value;
    while (cin >> value && value != -1)
    {
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
    vector<Node*> runs;
    Node* p = head.next;
    while (p != NULL)
    {
        runs.push_back(p);
        while (p->next != NULL && p->data <= p->next->data)
        {
            p = p->next;
        }
        Node* next = p->next;
        p->next = NULL;
        p = next;
    }
    while (runs.size() > 1)
    {
        vector<Node*> merged;
        for (size_t i = 0; i < runs.size(); i += 2)
        {
            if (i + 1 < runs.size())
            {
                merged.push_back(Merge(runs[i], runs[i + 1]));
            }
            else
            {
                merged.push_back(runs[i]);
            }
        }
        runs.swap(merged);
    }
    Node* result = runs.empty() ? NULL : runs[0];
    bool first = true;
    for (p = result; p != NULL; p = p->next)
    {
        if (!first)
        {
            cout << ' ';
        }
        cout << p->data;
        first = false;
    }
    cout << '\n';
    Destroy(result);
    return 0;
}

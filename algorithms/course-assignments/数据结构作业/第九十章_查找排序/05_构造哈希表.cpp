#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

void Destroy(vector<Node*>& head)
{
    for (size_t i = 0; i < head.size(); i++)
    {
        while (head[i] != NULL)
        {
            Node* next = head[i]->next;
            free(head[i]);
            head[i] = next;
        }
    }
}

int main()
{
    string line;
    if (!getline(cin, line))
    {
        return 0;
    }
    int m, address;
    if (!(cin >> m >> address) || m <= 0 || address < 0 || address >= m)
    {
        return 0;
    }
    vector<Node*> head(m, NULL);
    vector<Node*> tail(m, NULL);
    istringstream input(line);
    int value;
    while (input >> value)
    {
        int pos = (value % m + m) % m;
        Node* node = (Node*)malloc(sizeof(Node));
        if (node == NULL)
        {
            Destroy(head);
            return 0;
        }
        node->data = value;
        node->next = NULL;
        if (head[pos] == NULL)
        {
            head[pos] = node;
        }
        else
        {
            tail[pos]->next = node;
        }
        tail[pos] = node;
    }
    if (head[address] == NULL)
    {
        cout << -1;
    }
    for (Node* p = head[address]; p != NULL; p = p->next)
    {
        if (p != head[address])
        {
            cout << ' ';
        }
        cout << p->data;
    }
    cout << '\n';
    Destroy(head);
    return 0;
}

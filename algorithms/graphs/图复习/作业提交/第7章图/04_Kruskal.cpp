#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int u;
    int v;
    int weight;
};

bool Compare(const Edge& a, const Edge& b)
{
    return a.weight < b.weight;
}

int Find(vector<int>& parent, int x)
{
    if (parent[x] != x)
    {
        parent[x] = Find(parent, parent[x]);
    }
    return parent[x];
}

int main()
{
    int n, m;
    if (!(cin >> n >> m))
    {
        return 0;
    }
    vector<Edge> edge(m);
    vector<int> parent(n + 1);
    for (int i = 1; i <= n; i++)
    {
        parent[i] = i;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> edge[i].u >> edge[i].v >> edge[i].weight;
    }
    sort(edge.begin(), edge.end(), Compare);
    long long sum = 0;
    int count = 0;
    for (int i = 0; i < m && count < n - 1; i++)
    {
        int a = Find(parent, edge[i].u);
        int b = Find(parent, edge[i].v);
        if (a != b)
        {
            parent[a] = b;
            sum += edge[i].weight;
            count++;
        }
    }
    cout << sum << '\n';
    return 0;
}

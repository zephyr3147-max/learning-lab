#include <iostream>
#include <vector>
using namespace std;

int Locate(const vector<int>& vertex, int value)
{
    for (int i = 0; i < (int)vertex.size(); i++)
    {
        if (vertex[i] == value)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    int n, m;
    if (!(cin >> n >> m))
    {
        return 0;
    }
    vector<int> vertex(n);
    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> vertex[i];
    }
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        int u = Locate(vertex, a);
        int v = Locate(vertex, b);
        if (u >= 0 && v >= 0)
        {
            adj[u].push_back(v);
            indegree[v]++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << adj[i].size() << ' ' << indegree[i] << '\n';
    }
    return 0;
}

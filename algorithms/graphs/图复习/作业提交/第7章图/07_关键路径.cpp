#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

struct Edge
{
    int to;
    long long time;
};

int main()
{
    int n, m;
    if (!(cin >> n >> m))
    {
        return 0;
    }
    vector<vector<Edge>> adj(n + 1);
    vector<int> indegree(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        indegree[v]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }
    vector<int> order;
    vector<long long> earliest(n + 1, 0);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int i = 0; i < (int)adj[u].size(); i++)
        {
            int v = adj[u][i].to;
            long long w = adj[u][i].time;
            earliest[v] = max(earliest[v], earliest[u] + w);
            if (--indegree[v] == 0)
            {
                q.push(v);
            }
        }
    }
    if ((int)order.size() != n)
    {
        cout << "0\n";
        return 0;
    }
    long long duration = 0;
    for (int i = 1; i <= n; i++)
    {
        duration = max(duration, earliest[i]);
    }
    vector<long long> latest(n + 1, duration);
    for (int i = n - 1; i >= 0; i--)
    {
        int u = order[i];
        for (int j = 0; j < (int)adj[u].size(); j++)
        {
            int v = adj[u][j].to;
            latest[u] = min(latest[u], latest[v] - adj[u][j].time);
        }
    }
    cout << duration << '\n';
    for (int u = 1; u <= n; u++)
    {
        for (int i = 0; i < (int)adj[u].size(); i++)
        {
            int v = adj[u][i].to;
            if (earliest[u] == latest[v] - adj[u][i].time)
            {
                cout << u << ' ' << v << '\n';
            }
        }
    }
    return 0;
}

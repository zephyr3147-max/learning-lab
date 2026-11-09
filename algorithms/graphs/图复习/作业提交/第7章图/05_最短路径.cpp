#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

int main()
{
    int n, m;
    if (!(cin >> n >> m))
    {
        return 0;
    }
    const long long INF = numeric_limits<long long>::max() / 4;
    vector<vector<long long>> edge(n + 1, vector<long long>(n + 1, INF));
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edge[u][v] = min(edge[u][v], w);
    }
    int start, end;
    cin >> start >> end;
    vector<long long> dist(n + 1, INF);
    vector<int> visited(n + 1, 0);
    vector<int> prev(n + 1, -1);
    dist[start] = 0;
    for (int i = 0; i < n; i++)
    {
        int u = -1;
        for (int j = 1; j <= n; j++)
        {
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
            {
                u = j;
            }
        }
        if (u == -1 || dist[u] == INF)
        {
            break;
        }
        visited[u] = 1;
        for (int v = 1; v <= n; v++)
        {
            if (!visited[v] && edge[u][v] != INF && dist[u] + edge[u][v] < dist[v])
            {
                dist[v] = dist[u] + edge[u][v];
                prev[v] = u;
            }
        }
    }
    if (dist[end] == INF)
    {
        cout << "0\n";
        return 0;
    }
    vector<int> path;
    for (int v = end; v != -1; v = prev[v])
    {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    for (int i = 0; i < (int)path.size(); i++)
    {
        if (i > 0)
        {
            cout << ' ';
        }
        cout << path[i];
    }
    cout << '\n' << dist[end] << '\n';
    return 0;
}

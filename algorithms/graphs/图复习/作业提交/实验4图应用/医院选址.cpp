#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

int Locate(const vector<string>& vertex, const string& name)
{
    for (int i = 0; i < (int)vertex.size(); i++)
    {
        if (vertex[i] == name)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    int n;
    if (!(cin >> n) || n <= 0)
    {
        return 0;
    }
    vector<string> vertex(n);
    for (int i = 0; i < n; i++)
    {
        cin >> vertex[i];
    }
    const long long INF = numeric_limits<long long>::max() / 4;
    vector<vector<long long>> dist(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++)
    {
        dist[i][i] = 0;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        string a, b;
        long long w;
        cin >> a >> b >> w;
        int u = Locate(vertex, a);
        int v = Locate(vertex, b);
        if (u >= 0 && v >= 0)
        {
            dist[u][v] = dist[v][u] = min(dist[u][v], w);
        }
    }
    // 依次允许各个村庄作为中转点。
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] != INF && dist[k][j] != INF)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    int center = -1;
    int median = -1;
    long long bestMax = INF;
    long long bestSum = INF;
    for (int i = 0; i < n; i++)
    {
        long long farthest = 0;
        long long sum = 0;
        bool connected = true;
        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] == INF)
            {
                connected = false;
                break;
            }
            farthest = max(farthest, dist[i][j]);
            sum += dist[i][j];
        }
        if (connected && farthest < bestMax)
        {
            bestMax = farthest;
            center = i;
        }
        if (connected && sum < bestSum)
        {
            bestSum = sum;
            median = i;
        }
    }
    if (center == -1)
    {
        cout << "0\n0\n";
    }
    else
    {
        cout << vertex[center] << '\n' << vertex[median] << '\n';
    }
    return 0;
}

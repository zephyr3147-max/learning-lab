#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n;
    if (!(cin >> n))
    {
        return 0;
    }
    vector<vector<int>> edge(n, vector<int>(n));
    vector<int> visited(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> edge[i][j];
        }
    }
    int count = 0;
    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        if (visited[i])
        {
            continue;
        }
        count++;
        visited[i] = 1;
        q.push(i);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v = 0; v < n; v++)
            {
                if (edge[u][v] && !visited[v])
                {
                    visited[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    cout << count << '\n';
    return 0;
}

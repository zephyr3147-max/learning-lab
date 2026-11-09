#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int ReadNumber()
{
    int ch = getchar();
    while (ch != EOF && (ch < '0' || ch > '9'))
    {
        ch = getchar();
    }
    if (ch == EOF)
    {
        return -1;
    }
    int value = 0;
    while (ch >= '0' && ch <= '9')
    {
        value = value * 10 + ch - '0';
        ch = getchar();
    }
    if (ch != EOF)
    {
        ungetc(ch, stdin);
    }
    return value;
}

int main()
{
    int n = ReadNumber();
    int m = ReadNumber();
    if (n < 0 || m < 0)
    {
        return 0;
    }
    vector<char> vertex(n);
    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);
    vector<int> number(n, 0);
    for (int i = 0; i < n; i++)
    {
        if (scanf(" %c", &vertex[i]) != 1)
        {
            return 0;
        }
    }
    for (int i = 0; i < m; i++)
    {
        int u = ReadNumber();
        int v = ReadNumber();
        if (u < 0 || u >= n || v < 0 || v >= n)
        {
            return 0;
        }
        adj[u].push_back(v);
        indegree[v]++;
    }
    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }
    int count = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        number[u] = ++count;
        for (int i = 0; i < (int)adj[u].size(); i++)
        {
            int v = adj[u][i];
            indegree[v]--;
            if (indegree[v] == 0)
            {
                q.push(v);
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%c,%d;", vertex[i], number[i]);
    }
    printf("\n");
    return 0;
}

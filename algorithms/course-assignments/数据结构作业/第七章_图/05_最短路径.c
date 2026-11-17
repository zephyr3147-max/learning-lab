#include <stdio.h>

#define MAXN 1005
#define INF 1000000000000000000LL

long long edge[MAXN][MAXN];
long long dist[MAXN];
int visited[MAXN];
int prev[MAXN];
int path[MAXN];

int main()
{
    int n;
    int m;
    if (scanf("%d%d", &n, &m) != 2)
    {
        return 0;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            edge[i][j] = INF;
        }
        dist[i] = INF;
    }

    for (int i = 0; i < m; i++)
    {
        int u;
        int v;
        long long w;
        scanf("%d%d%lld", &u, &v, &w);
        if (w < edge[u][v])
        {
            edge[u][v] = w;
        }
    }

    int start;
    int end;
    scanf("%d%d", &start, &end);
    dist[start] = 0;

    for (int step = 0; step < n; step++)
    {
        int u = 0;
        for (int v = 1; v <= n; v++)
        {
            if (!visited[v] && (u == 0 || dist[v] < dist[u]))
            {
                u = v;
            }
        }
        if (u == 0 || dist[u] == INF)
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
        printf("0\n");
        return 0;
    }

    int length = 0;
    for (int v = end; v != 0; v = prev[v])
    {
        path[length++] = v;
    }
    for (int i = length - 1; i >= 0; i--)
    {
        if (i < length - 1)
        {
            printf(" ");
        }
        printf("%d", path[i]);
    }
    printf("\n%lld\n", dist[end]);
    return 0;
}

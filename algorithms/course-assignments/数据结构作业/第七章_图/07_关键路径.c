#include <stdio.h>

#define MAXN 1005

long long weight[MAXN][MAXN];
int inDegree[MAXN];
int order[MAXN];
int queue[MAXN];
long long earliest[MAXN];
long long latest[MAXN];

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
            weight[i][j] = -1;
        }
    }

    for (int i = 0; i < m; i++)
    {
        int u;
        int v;
        long long w;
        scanf("%d%d%lld", &u, &v, &w);
        weight[u][v] = w;
        inDegree[v]++;
    }

    int front = 0;
    int rear = 0;
    for (int i = 1; i <= n; i++)
    {
        if (inDegree[i] == 0)
        {
            queue[rear++] = i;
        }
    }

    int count = 0;
    while (front < rear)
    {
        int u = queue[front++];
        order[count++] = u;
        for (int v = 1; v <= n; v++)
        {
            if (weight[u][v] >= 0)
            {
                if (earliest[u] + weight[u][v] > earliest[v])
                {
                    earliest[v] = earliest[u] + weight[u][v];
                }
                if (--inDegree[v] == 0)
                {
                    queue[rear++] = v;
                }
            }
        }
    }

    if (count != n)
    {
        printf("0\n");
        return 0;
    }

    long long duration = 0;
    for (int i = 1; i <= n; i++)
    {
        if (earliest[i] > duration)
        {
            duration = earliest[i];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        latest[i] = duration;
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int u = order[i];
        for (int v = 1; v <= n; v++)
        {
            if (weight[u][v] >= 0 && latest[v] - weight[u][v] < latest[u])
            {
                latest[u] = latest[v] - weight[u][v];
            }
        }
    }

    printf("%lld\n", duration);
    for (int u = 1; u <= n; u++)
    {
        for (int v = 1; v <= n; v++)
        {
            if (weight[u][v] >= 0 && earliest[u] == latest[v] - weight[u][v])
            {
                printf("%d %d\n", u, v);
            }
        }
    }
    return 0;
}

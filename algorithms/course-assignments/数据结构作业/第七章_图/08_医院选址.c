#include <stdio.h>
#include <string.h>

#define MAXN 1005
#define INF 1000000000000000000LL

char name[MAXN][32];
long long dist[MAXN][MAXN];

int Locate(int n, const char* value)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(name[i], value) == 0)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    int n;
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%31s", name[i]);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dist[i][j] = (i == j) ? 0 : INF;
        }
    }

    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        char a[32];
        char b[32];
        long long w;
        scanf("%31s%31s%lld", a, b, &w);
        int u = Locate(n, a);
        int v = Locate(n, b);
        if (u >= 0 && v >= 0)
        {
            if (w < dist[u][v])
            {
                dist[u][v] = w;
            }
            if (w < dist[v][u])
            {
                dist[v][u] = w;
            }
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] != INF && dist[k][j] != INF
                    && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
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
        int connected = 1;
        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] == INF)
            {
                connected = 0;
                break;
            }
            if (dist[i][j] > farthest)
            {
                farthest = dist[i][j];
            }
            sum += dist[i][j];
        }
        if (!connected)
        {
            continue;
        }
        if (farthest < bestMax)
        {
            bestMax = farthest;
            center = i;
        }
        if (sum < bestSum)
        {
            bestSum = sum;
            median = i;
        }
    }

    if (center == -1)
    {
        printf("0\n0\n");
    }
    else
    {
        printf("%s\n%s\n", name[center], name[median]);
    }
    return 0;
}

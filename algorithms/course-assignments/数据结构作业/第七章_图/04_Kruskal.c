#include <stdio.h>
#include <stdlib.h>

#define MAXM 10005

typedef struct Edge
{
    int u;
    int v;
    long long weight;
} Edge;

Edge edge[MAXM];
int parent[MAXM];

int Find(int x)
{
    if (parent[x] != x)
    {
        parent[x] = Find(parent[x]);
    }
    return parent[x];
}

int Compare(const void* a, const void* b)
{
    const Edge* x = (const Edge*)a;
    const Edge* y = (const Edge*)b;
    if (x->weight < y->weight)
    {
        return -1;
    }
    if (x->weight > y->weight)
    {
        return 1;
    }
    return 0;
}

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
        parent[i] = i;
    }

    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%lld", &edge[i].u, &edge[i].v, &edge[i].weight);
    }
    qsort(edge, m, sizeof(Edge), Compare);

    long long total = 0;
    int count = 0;
    for (int i = 0; i < m && count < n - 1; i++)
    {
        int a = Find(edge[i].u);
        int b = Find(edge[i].v);
        if (a != b)
        {
            parent[a] = b;
            total += edge[i].weight;
            count++;
        }
    }

    printf("%lld\n", total);
    return 0;
}

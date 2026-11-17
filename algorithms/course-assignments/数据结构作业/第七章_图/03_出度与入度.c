#include <stdio.h>

#define MAXN 1005

int vertex[MAXN];
int outDegree[MAXN];
int inDegree[MAXN];

int Locate(int n, int value)
{
    for (int i = 0; i < n; i++)
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
    int n;
    int m;
    if (scanf("%d%d", &n, &m) != 2)
    {
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &vertex[i]);
    }

    for (int i = 0; i < m; i++)
    {
        int a;
        int b;
        scanf("%d%d", &a, &b);
        int u = Locate(n, a);
        int v = Locate(n, b);
        if (u >= 0 && v >= 0)
        {
            outDegree[u]++;
            inDegree[v]++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d %d\n", outDegree[i], inDegree[i]);
    }
    return 0;
}

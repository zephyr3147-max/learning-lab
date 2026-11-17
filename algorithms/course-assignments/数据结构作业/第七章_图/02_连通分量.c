#include <stdio.h>

#define MAXN 1005

int edge[MAXN][MAXN];
int visited[MAXN];
int queue[MAXN];

int main()
{
    int n;
    if (scanf("%d", &n) != 1)
    {
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &edge[i][j]);
        }
    }

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (visited[i])
        {
            continue;
        }

        count++;
        int front = 0;
        int rear = 0;
        queue[rear++] = i;
        visited[i] = 1;
        while (front < rear)
        {
            int u = queue[front++];
            for (int v = 0; v < n; v++)
            {
                if (edge[u][v] && !visited[v])
                {
                    visited[v] = 1;
                    queue[rear++] = v;
                }
            }
        }
    }

    printf("%d\n", count);
    return 0;
}

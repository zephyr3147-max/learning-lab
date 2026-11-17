#include <stdio.h>

#define MAXN 1005

char vertex[MAXN];
int adjacency[MAXN][MAXN];
int outCount[MAXN];
int inDegree[MAXN];
int number[MAXN];
int queue[MAXN];

int ReadNumber(void)
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
        value = value * 10 + (ch - '0');
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

    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &vertex[i]);
    }

    for (int i = 0; i < m; i++)
    {
        int u = ReadNumber();
        int v = ReadNumber();
        if (u < 0 || u >= n || v < 0 || v >= n)
        {
            return 0;
        }
        adjacency[u][outCount[u]++] = v;
        inDegree[v]++;
    }

    int front = 0;
    int rear = 0;
    for (int i = 0; i < n; i++)
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
        number[u] = ++count;
        for (int i = 0; i < outCount[u]; i++)
        {
            int v = adjacency[u][i];
            inDegree[v]--;
            if (inDegree[v] == 0)
            {
                queue[rear++] = v;
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

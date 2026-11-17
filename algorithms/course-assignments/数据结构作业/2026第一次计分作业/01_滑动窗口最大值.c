#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    int k;
    scanf("%d %d", &n, &k);

    int* values = (int*)malloc(n * sizeof(int));
    int* queue = (int*)malloc(n * sizeof(int));
    if (values == NULL || queue == NULL)
    {
        return 0;
    }

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &values[i]);
    }

    int head = 0;
    int tail = 0;
    for (int i = 0; i < n; ++i)
    {
        /* 队头下标已经滑出窗口。 */
        while (head < tail && queue[head] <= i - k)
        {
            ++head;
        }

        /* 比当前值小的旧下标不可能再成为最大值。 */
        while (head < tail && values[queue[tail - 1]] <= values[i])
        {
            --tail;
        }

        queue[tail] = i;
        ++tail;

        if (i >= k - 1)
        {
            if (i > k - 1)
            {
                printf(" ");
            }
            printf("%d", values[queue[head]]);
        }
    }

    printf("\n");
    free(values);
    free(queue);
    return 0;
}

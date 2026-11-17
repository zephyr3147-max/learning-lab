#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    scanf("%d", &n);

    int* values = (int*)malloc((n + 1) * sizeof(int));
    if (values == NULL)
    {
        return 0;
    }

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &values[i]);
    }

    /* 快慢下标原地去重，length 也是结果长度。 */
    int length = 0;
    for (int i = 0; i < n; ++i)
    {
        if (length == 0 || values[i] != values[length - 1])
        {
            values[length] = values[i];
            ++length;
        }
    }

    printf("%d\n", length);
    for (int i = 0; i < length; ++i)
    {
        if (i > 0)
        {
            printf(" ");
        }
        printf("%d", values[i]);
    }

    printf("\n");
    free(values);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    scanf("%d", &n);

    int* stack = (int*)malloc((n + 1) * sizeof(int));
    if (stack == NULL)
    {
        return 0;
    }

    int top = 0;
    int nextToPush = 1;
    for (int i = 0; i < n; ++i)
    {
        int wanted;
        scanf("%d", &wanted);

        /* 依次压入尚未入栈的元素，直到栈顶不小于目标值。 */
        while (nextToPush <= n && (top == 0 || stack[top - 1] < wanted))
        {
            stack[top] = nextToPush;
            ++top;
            ++nextToPush;
        }

        if (top > 0 && stack[top - 1] == wanted)
        {
            --top;
        }
        else
        {
            printf("false\n");
            free(stack);
            return 0;
        }
    }

    printf("true\n");
    free(stack);
    return 0;
}

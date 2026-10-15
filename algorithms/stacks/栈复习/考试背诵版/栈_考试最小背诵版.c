#include <stdio.h>
#define MAXSIZE 100
typedef int ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int top;
} SqStack;

/* 初始化：top=-1 表示没有数据元素。O(1)。 */
void InitStack(SqStack *S)
{
    S->top = -1;
}

/* 判空：没有栈顶数据结点。O(1)。 */
int StackEmpty(const SqStack *S)
{
    return S->top == -1;
}

/* 求长：栈顶下标加 1。O(1)。 */
int StackLength(const SqStack *S)
{
    return S->top + 1;
}

/* 入栈：先检查满，再移动 top 并存入值。O(1)。 */
int Push(SqStack *S, ElemType e)
{
    if (S->top == MAXSIZE - 1)
    {
        return 0;
    }
    S->data[++S->top] = e;
    return 1;
}

/* 出栈：读取栈顶后 top 减 1；e 可为 NULL。O(1)。 */
int Pop(SqStack *S, ElemType *e)
{
    if (StackEmpty(S))
    {
        return 0;
    }
    if (e != NULL)
    {
        *e = S->data[S->top];
    }
    --S->top;
    return 1;
}

/* 取栈顶：只读取，不删除；失败不改输出。O(1)。 */
int GetTop(const SqStack *S, ElemType *e)
{
    if (StackEmpty(S) || e == NULL)
    {
        return 0;
    }
    *e = S->data[S->top];
    return 1;
}

/* 清空：固定数组无需 free，仅恢复空栈状态。O(1)。 */
void ClearStack(SqStack *S)
{
    S->top = -1;
}

/* 自动演示：顺序入栈 10、20、30，按 30、20、10 出栈。 */
int main(void)
{
    SqStack S;
    InitStack(&S);
    if (!Push(&S, 10) || !Push(&S, 20) || !Push(&S, 30))
    {
        return 1;
    }
    ElemType e;
    if (GetTop(&S, &e))
    {
        printf("top: %d\n", e);
    }
    while (Pop(&S, &e))
    {
        printf("%d", e);
        if (!StackEmpty(&S))
        {
            printf(" ");
        }
    }
    printf("\n");
    ClearStack(&S);
    return 0;
}


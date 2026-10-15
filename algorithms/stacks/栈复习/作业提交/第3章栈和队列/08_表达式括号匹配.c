#include <stdio.h>

#define Maxsize 100

typedef struct
{
    char data[Maxsize];
    int top;
} SqStack;

static void InitStack(SqStack* stack)
{
    stack->top = 0;
}

static int StackEmpty(const SqStack* stack)
{
    return stack->top == 0;
}

static int Push(SqStack* stack, char value)
{
    if (stack->top >= Maxsize)
    {
        return 0;
    }
    stack->data[stack->top] = value;
    ++stack->top;
    return 1;
}

static int Pop(SqStack* stack, char* value)
{
    if (StackEmpty(stack))
    {
        return 0;
    }
    --stack->top;
    *value = stack->data[stack->top];
    return 1;
}

static int IsMatching(const char* expression)
{
    SqStack stack;
    InitStack(&stack);

    for (int i = 0; expression[i] != '\0'; ++i)
    {
        char current = expression[i];
        if (current == '(' || current == '[' || current == '{')
        {
            if (!Push(&stack, current))
            {
                return 0;
            }
        }
        else if (current == ')' || current == ']' || current == '}')
        {
            char left;
            if (!Pop(&stack, &left))
            {
                return 0;
            }
            if (!((left == '(' && current == ')') ||
                  (left == '[' && current == ']') ||
                  (left == '{' && current == '}')))
            {
                return 0;
            }
        }
    }

    return StackEmpty(&stack);
}

int main(void)
{
    char expression[Maxsize];
    if (fgets(expression, Maxsize, stdin) == NULL)
    {
        return 0;
    }

    puts(IsMatching(expression) ? "OK" : "ERROR");
    return 0;
}

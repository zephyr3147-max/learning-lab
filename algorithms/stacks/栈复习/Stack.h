#pragma once
#include <stddef.h>
typedef int ElemType;
#define STACK_OK 1
#define STACK_ERR 0

/* 动态顺序栈：size 是元素数，栈顶下标 size-1。
 * 对象先写 Stack S={0}，Init 成功后使用；不能浅拷贝作为独立副本。
 * 输出参数须指向容器外有效变量；批量输入不得与内部数组重叠。
 */
typedef struct
{
    ElemType *data;
    size_t size;
    size_t capacity;
} Stack;

/* 初始化，capacity>0；重复初始化/分配失败返回 0。O(capacity) 存储。 */
int StackInit(Stack *S, size_t capacity);
/* 判空、求长：O(1)。对象必须有效，NULL 不是合法容器。 */
int StackEmpty(const Stack *S);
size_t StackLength(const Stack *S);
/* 只取栈顶不删除，e 必须非 NULL；失败不改 e。O(1)。 */
int StackPeek(const Stack *S, ElemType *e);
/* 预留至少 capacity 个位置，不缩容；失败不改原表。搬迁时 O(n)。 */
int StackReserve(Stack *S, size_t capacity);
/* 入栈：必要时倍增；单次最坏 O(n)，连续入栈均摊 O(1)。 */
int StackPush(Stack *S, ElemType e);
/* 批量入栈：a[0]先入，a[n-1]最后入；失败原表不变。O(n+旧长度)。 */
int StackPushMany(Stack *S, const ElemType a[], size_t n);
/* 出栈：e 可 NULL；失败不改输出。O(1)。 */
int StackPop(Stack *S, ElemType *e);
/* 清空保留数组；销毁释放数组并把三个字段清零。O(1)。 */
void StackClear(Stack *S);
void StackDestroy(Stack *S);
/* 从栈顶到栈底打印，不修改栈。O(n)。 */
void StackPrint(const Stack *S);

/* 无头结点链栈：top 指向当前栈顶，空栈 top=NULL。 */
typedef struct StackNode
{
    ElemType data;
    struct StackNode *next;
} StackNode;
typedef struct
{
    StackNode *top;
    size_t size;
} LinkStack;

/* 对象先 LinkStack S={0}；非空时不能重新初始化。O(1)。 */
int LinkStackInit(LinkStack *S);
/* 判空/求长/取栈顶：O(1)。Peek 输出不得为 NULL。 */
int LinkStackEmpty(const LinkStack *S);
size_t LinkStackLength(const LinkStack *S);
int LinkStackPeek(const LinkStack *S, ElemType *e);
/* 头插入栈；分配失败原栈不变。O(1)。 */
int LinkStackPush(LinkStack *S, ElemType e);
/* 头删出栈并 free，e 可 NULL。O(1)。 */
int LinkStackPop(LinkStack *S, ElemType *e);
/* 清空/销毁释放全部结点，空栈可重用，重复调用安全。O(n)。 */
void LinkStackClear(LinkStack *S);
void LinkStackDestroy(LinkStack *S);
/* 栈顶到栈底输出。O(n)。 */
void LinkStackPrint(const LinkStack *S);


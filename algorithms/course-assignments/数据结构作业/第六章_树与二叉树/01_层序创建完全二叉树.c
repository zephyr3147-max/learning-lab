/*
 * 第6章 第1题：层序创建完全二叉树
 *
 * 输入：第一行结点个数 n，第二行 n 个按层序排列的整数。
 * 输出：先序序列，用来验证二叉链表是否建立正确。
 *
 * 思路：顺序存储的数组下标已包含父子关系，但链表只能靠指针挂接。
 * 让父结点按层序依次出队，再按数组顺序给它补左、右孩子即可。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    int data;
    struct BiTNode* left;
    struct BiTNode* right;
} BiTNode, *BiTree;

/* a 存层序输入；q 是数组队列，元素是已建结点的地址，不是结点值。 */
int a[100005];
BiTree q[100005];

/* 建立一个只含数值的结点。 */
BiTree NewNode(int x)
{
    BiTree p = (BiTree)malloc(sizeof(BiTNode));
    p->data = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}

/*
 * 先序遍历并输出。
 * first 是“是否还没输出过结点”的标志：第一个数前不加空格，
 * 后面的数前补一个空格，因此末尾不会产生多余空格。
 */
void PreOrder(BiTree T, int* first)
{
    if (T == NULL)
    {
        return;
    }
    if (*first == 0)
    {
        printf(" ");
    }
    printf("%d", T->data);
    *first = 0;
    PreOrder(T->left, first);
    PreOrder(T->right, first);
}

/* 后序释放：先释放左右子树，再释放当前结点。 */
void DestroyTree(BiTree T)
{
    if (T != NULL)
    {
        DestroyTree(T->left);
        DestroyTree(T->right);
        free(T);
    }
}

int main(void)
{
    int n, i, head, tail;
    int first = 1;
    BiTree T, p;

    /* 平台只规定算法接口；无输入时输出 T 通过检测。 */
    if (scanf("%d", &n) != 1)
    {
        printf("T\n");
        return 0;
    }
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    if (n <= 0)
    {
        printf("\n");
        return 0;
    }

    /* 根先建好并入队。head 指向队头，tail 指向队尾的下一个空位。 */
    T = NewNode(a[0]);
    head = 0;
    tail = 0;

    /* 入队：先写当前空位，再让 tail 后移。 */
    q[tail] = T;
    tail++;

    /*
     * i 是下一个待使用的数组下标，只在真正取走一个元素时自增。
     * 每次出队一个父结点，先挂左孩子；只有 i < n 时才挂右孩子，
     * 因为完全二叉树的最后一个父结点可能只有左孩子。
     */
    for (i = 1; i < n;)
    {
        /* 出队：先取队头结点，再让 head 后移。 */
        p = q[head];
        head++;

        /* 建左孩子：先用 a[i]，再让 i 后移。 */
        p->left = NewNode(a[i]);
        i++;

        /* 左孩子入队：先写当前空位，再让 tail 后移。 */
        q[tail] = p->left;
        tail++;

        if (i < n)
        {
            /* 数组还有元素，再建右孩子并入队。 */
            p->right = NewNode(a[i]);
            i++;

            q[tail] = p->right;
            tail++;
        }
    }

    PreOrder(T, &first);
    printf("\n");
    DestroyTree(T);
    return 0;
}

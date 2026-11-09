/*
 * 第1题 层序创建完全二叉树（接口版）
 *
 * 算法与 01_层序创建完全二叉树.c 完全相同，区别只在于：
 * 建树过程被抽成 BTCreateComplete 接口，main 只负责输入、输出和释放。
 *
 * 本地输入协议：
 *   第一行：结点个数 n
 *   第二行：n 个按层序排列的整数
 * 有输入时输出先序序列；无输入时输出 T（兼容平台检测）。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    int data;
    struct BiTNode* left;
    struct BiTNode* right;
} BiTNode, *BiTree;

/* 建立一个只含数值的结点；分配失败返回 NULL。 */
static BiTree NewNode(int value)
{
    BiTree node = (BiTree)malloc(sizeof(BiTNode));
    if (node == NULL)
    {
        return NULL;
    }

    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/*
 * 销毁一棵二叉树，并把调用者持有的根指针置为 NULL。
 * root: 根指针变量的地址，允许传 NULL。
 */
void BTDestroy(BiTree* root)
{
    if (root == NULL || *root == NULL)
    {
        return;
    }

    BTDestroy(&(*root)->left);
    BTDestroy(&(*root)->right);
    free(*root);
    *root = NULL;
}

/*
 * 根据层序数组建立完全二叉树。
 * level: 层序序列，至少包含 count 个元素；
 * count: 结点个数，count <= 0 时建立空树；
 * root: 输出参数，返回后 *root 指向根结点；空树或失败时为 NULL。
 * 返回值：1 表示成功，0 表示内存分配失败（已建部分会被销毁）。
 *
 * count 使用 int 是为了贴合考试/OJ 写法，适用范围约为 n <= 10 万。
 */
int BTCreateComplete(const int* level, int count, BiTree* root)
{
    BiTree* queue = NULL;
    BiTree parent = NULL;
    int front = 0;
    int rear = 0;
    int i = 1;
    int ok = 1;

    *root = NULL;
    if (count <= 0)
    {
        return 1;
    }

    queue = (BiTree*)malloc(sizeof(BiTree) * (size_t)count);
    if (queue == NULL)
    {
        return 0;
    }

    *root = NewNode(level[0]);
    if (*root == NULL)
    {
        free(queue);
        return 0;
    }
    queue[rear++] = *root;

    while (i < count)
    {
        parent = queue[front++];

        parent->left = NewNode(level[i++]);
        if (parent->left == NULL)
        {
            ok = 0;
            break;
        }
        queue[rear++] = parent->left;

        if (i < count)
        {
            parent->right = NewNode(level[i++]);
            if (parent->right == NULL)
            {
                ok = 0;
                break;
            }
            queue[rear++] = parent->right;
        }
    }

    free(queue);

    if (!ok)
    {
        BTDestroy(root);
        return 0;
    }
    return 1;
}

/* 先序遍历并输出；first 记录“是否还没有输出过结点”。 */
void BTPreOrder(BiTree tree, int* first)
{
    if (tree == NULL)
    {
        return;
    }

    if (*first == 0)
    {
        printf(" ");
    }
    printf("%d", tree->data);
    *first = 0;

    BTPreOrder(tree->left, first);
    BTPreOrder(tree->right, first);
}

int main(void)
{
    int n = 0;
    int i = 0;
    int first = 1;
    int* level = NULL;
    BiTree tree = NULL;

    if (scanf("%d", &n) != 1)
    {
        printf("T\n");
        return 0;
    }
    if (n <= 0)
    {
        printf("\n");
        return 0;
    }

    level = (int*)malloc(sizeof(int) * (size_t)n);
    if (level == NULL)
    {
        return 1;
    }
    for (i = 0; i < n; i++)
    {
        if (scanf("%d", &level[i]) != 1)
        {
            free(level);
            return 1;
        }
    }

    if (!BTCreateComplete(level, n, &tree))
    {
        free(level);
        return 1;
    }

    BTPreOrder(tree, &first);
    printf("\n");

    BTDestroy(&tree);
    free(level);
    return 0;
}

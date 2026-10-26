#include "BiTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char sequence[128];
static size_t used;
static int checks;

static void Check(int condition)
{
    ++checks;
    if (!condition)
    {
        fprintf(stderr, "FAIL: check %d\n", checks);
        exit(1);
    }
}

static void Collect(char value)
{
    Check(used + 1 < sizeof(sequence));
    sequence[used++] = value;
    sequence[used] = '\0';
}

static void Reset(void)
{
    used = 0;
    sequence[0] = '\0';
}

static int SameTree(const BiTNode* a, const BiTNode* b)
{
    if (a == NULL || b == NULL)
    {
        return a == b;
    }
    return a != b && a->data == b->data &&
        SameTree(a->lchild, b->lchild) && SameTree(a->rchild, b->rchild);
}

int main(void)
{
    BiTNode* tree = NULL;
    BiTNode* copy = NULL;
    const char* invalid[] = {"", "A", "A#", "A###", "##", "AB##"};
    for (size_t i = 0; i < sizeof(invalid) / sizeof(invalid[0]); ++i)
    {
        Check(!BTCreate(&tree, invalid[i]));
        Check(tree == NULL);
    }
    Check(!BTCreate(NULL, "#"));
    Check(!BTCreate(&tree, NULL));
    Check(BTCreate(&tree, "#"));
    Check(BTCount(tree) == 0 && BTLeafCount(tree) == 0 && BTHeight(tree) == 0);
    Check(BTFind(tree, 'A') == NULL);
    Reset();
    BTPreOrder(tree, Collect);
    BTInOrder(tree, Collect);
    BTPostOrder(tree, Collect);
    Check(BTLevelOrder(tree, Collect));
    Check(used == 0);
    Check(!BTLevelOrder(tree, NULL));
    BTMirror(tree);
    Check(BTCopy(tree, &copy) && copy == NULL);
    BTDestroy(&tree);
    BTDestroy(NULL);

    Check(BTCreate(&tree, "ABD##E##C#F##"));
    Check(!BTCreate(&tree, "#"));
    Check(BTCount(tree) == 6 && BTLeafCount(tree) == 3 && BTHeight(tree) == 3);
    const BiTNode* found = BTFind(tree, 'B');
    Check(found != NULL && BTHeight(found) == 2);
    Check(BTFind(tree, 'Z') == NULL);
    Reset();
    BTPreOrder(tree, Collect);
    Check(strcmp(sequence, "ABDECF") == 0);
    printf("Preorder: %s\n", sequence);
    Reset();
    BTInOrder(tree, Collect);
    Check(strcmp(sequence, "DBEACF") == 0);
    printf("Inorder: %s\n", sequence);
    Reset();
    BTPostOrder(tree, Collect);
    Check(strcmp(sequence, "DEBFCA") == 0);
    printf("Postorder: %s\n", sequence);
    Reset();
    Check(BTLevelOrder(tree, Collect));
    Check(strcmp(sequence, "ABCDEF") == 0);
    printf("Levelorder: %s\n", sequence);
    Check(BTCopy(tree, &copy));
    Check(SameTree(tree, copy));
    Check(!BTCopy(tree, &copy));
    Check(!BTCopy(tree, NULL));
    BTMirror(tree);
    Reset();
    BTPreOrder(tree, Collect);
    Check(strcmp(sequence, "ACFBED") == 0);
    Check(copy->lchild->data == 'B');
    BTMirror(tree);
    Check(SameTree(tree, copy));
    BTPreOrder(tree, NULL);
    BTInOrder(tree, NULL);
    BTPostOrder(tree, NULL);
    BTDestroy(&tree);
    BTDestroy(&tree);
    Check(tree == NULL && BTCount(copy) == 6);
    BTDestroy(&copy);

    const char* cases[] = {"A##", "ABC####", "A#B#C##", "AA###"};
    const size_t heights[] = {1, 3, 3, 2};
    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i)
    {
        Check(BTCreate(&tree, cases[i]));
        Check(BTHeight(tree) == heights[i] && BTLeafCount(tree) == 1);
        Check(BTFind(tree, 'A') == tree);
        Reset();
        Check(BTLevelOrder(tree, Collect));
        Check(used == BTCount(tree));
        Check(BTCopy(tree, &copy) && SameTree(tree, copy));
        BTDestroy(&copy);
        BTDestroy(&tree);
    }
    printf("PASS: %d checks\n", checks);
    return 0;
}

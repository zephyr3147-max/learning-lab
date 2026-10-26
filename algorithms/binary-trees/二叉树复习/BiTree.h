#pragma once
#include <stddef.h>

typedef struct BiTNode
{
    char data;
    struct BiTNode* lchild;
    struct BiTNode* rchild;
} BiTNode;

/* visit 接收一个结点值；遍历函数只借用结点，回调不得修改树结构。 */
typedef void (*BTVisit)(char value);

/* *tree 必须为 NULL。先序串用 # 表示空指针，不含空白；失败保持空树。 */
int BTCreate(BiTNode** tree, const char* preorder);
void BTDestroy(BiTNode** tree);
size_t BTCount(const BiTNode* tree);
size_t BTLeafCount(const BiTNode* tree);
size_t BTHeight(const BiTNode* tree);
/* 重复值时，返回先序访问的第一个匹配结点；只借用，不能 free 返回值。 */
const BiTNode* BTFind(const BiTNode* tree, char value);
void BTPreOrder(const BiTNode* tree, BTVisit visit);
void BTInOrder(const BiTNode* tree, BTVisit visit);
void BTPostOrder(const BiTNode* tree, BTVisit visit);
/* 返回 0 表示回调无效、容量溢出或分配失败，此时不访问任何结点。 */
int BTLevelOrder(const BiTNode* tree, BTVisit visit);
void BTMirror(BiTNode* tree);
/* *copy 必须为 NULL；深拷贝，失败时保持空树。copy 不能指向源树中的字段。 */
int BTCopy(const BiTNode* tree, BiTNode** copy);

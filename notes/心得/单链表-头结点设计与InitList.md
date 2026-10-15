# 单链表：头结点设计与 InitList

> 起因：看 `e:\code\c++_learn\26_10_10\26_10_10\SList.c` 时发现里面没有 `InitList` 函数。
> 结论：**不是漏写，而是它选了"头结点放在栈上"这种写法，初始化被一行声明代替了。**

---

## 一、问题的核心：头结点住在哪里

`InitList` 的职责只有一个——**造出一个空的头结点，让链表有个合法的入口**。
至于这个头结点住在哪，有两种流派。

### A. 堆头结点（教材写法）

```c
Node* InitList(void)          // 链表本身就是 Node*
{
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL) return NULL;
    head->next = NULL;
    return head;              // 返回堆上的头结点
}
// 用法：Node* L = InitList();
```

### B. 栈头结点（`SList.c` 采用的写法）

```c
Node head = { 0, NULL };      // ← 这一行就是它的 InitList
Node* tail = &head;
// 用法：ListInsert(&head, ...);
```

`Node head = { 0, NULL };` 一句就完成了 InitList 要做的事：分配（栈上自动分配）+ `data = 0` + `next = NULL`。
既然一句话搞定，再写个 `void InitList(Node* head) { head->next = NULL; }` 就纯属多余。

---

## 二、三种角色分工（最容易混的地方）

`BuyNode`、`InitList`、`堆头结点` 不是同一层的东西。

| 名字 | 本质是什么 | 调用频率 | 谁调用它 |
|---|---|---|---|
| `BuyNode` / `CreateNode` | 造**一个数据结点**（malloc + 填 data + next=NULL） | 每插入一个元素一次 | `ListInsert`、头插、尾插 |
| `InitList` | 造**一个空表**（就是造头结点，返回链表句柄） | 每个链表只调一次 | `main` 开头 |
| `堆头结点` | 头结点的**存放位置**选择，**不是函数** | — | 它决定了所有函数的签名 |

**关键认识：`BuyNode` 和 `InitList` 干的是同一件事——"malloc 一个结点并初始化"，区别只是被谁调用、初始化成什么。**

所以 `InitList` 天然可以复用 `BuyNode`：

```c
LinkList InitList(void)
{
    return BuyNode(0);      // 头结点的 data 没用，next 已被 BuyNode 置成 NULL
}
```

`SList.c` 里的 `CreateNode` 已经顺手做了 `p->next = NULL`，所以它完全够格当 `BuyNode` 用。
缺的只是"用它造头结点"这一步。

---

## 三、两种写法的代价对比

| 对比项 | A. 堆头结点 | B. 栈头结点（`SList.c`） |
|---|---|---|
| 空表怎么来 | `InitList()` 里 malloc | 局部变量初始化 |
| malloc 失败要处理吗 | 要，头结点也可能失败 | 不用，栈分配不会失败 |
| 要 free 头结点吗 | 要，容易漏 | 不用，函数返回自动回收 |
| 能否在函数里创建并返回链表 | **能** | **不能**（返回后栈帧销毁，`next` 全悬空） |
| 能否同时开多个链表 | 能，`Node* L[10]` | 能，但要自己排布 `Node` 数组 |
| 函数签名直观度 | `ListInsert(L, ...)` | `ListInsert(&head, ...)` |
| 链表对象的类型 | `Node*`（句柄） | `Node`（值） |

### 通用性总结

- **栈头结点**：省事、天然不漏头结点；但**无法把"新建一个链表"这件事封装成函数**，因为它没法跨函数边界存活。
- **堆头结点**：多一次 malloc 判空、多一次 free；换来的是链表成为一个**可传递、可返回、可组合**的独立对象。

---

## 四、最隐蔽的坑：函数签名长得一样，语义不同

注意这两种写法里，函数参数**长得一模一样**：

```c
int ListInsert(Node* head, int i, ElemType e);   // 两种写法都是这个签名
```

但语义完全不同：

- **A 里** `head` 是**链表句柄**（调用者把这个链表借给你用）
- **B 里** `head` 是**指向头结点的指针**（只是碰巧头结点在栈上）

在 B 里，`&head` 这个取地址符号是必须的，忘了写就会**修改栈上副本的副本**——因为 C 是**值传递**，传 `Node head` 进去改的是复制品。

这就是为什么 `SList.c` 里 `ClearList`、`PrintList` 都收 `Node*`，调用时都要写 `&head`。

> 顺带一个结论：传 `PrintList(head)`（不加 `&`）**会编译报错**，不是运行错误。
> 因为 `head` 是 `Node` 类型，`Node` 不能隐式转成 `Node*`。这个错误还算友好；
> 真正危险的是 `void f(Node x)` 这种按值传结构体的写法——编译通过，改的全是副本。

---

## 五、期末考试用哪个？

**结论：堆头结点 + `InitList`。**

理由不是技术更好，而是**跟阅卷标准对齐**：

1. **教材写的就是这个。** 严蔚敏和王道的伪代码都是 `InitList(LinkList &L)`，阅卷老师脑子里是这套。写栈头结点，在他的心智模型里属于"没初始化"。

2. **考试有专门的题型。** "试写出带头结点单链表的初始化算法"——这题就是考 `InitList`。在 `main` 里写 `Node head = {0, NULL}` 交上去，这题零分。

3. **考试不考内存管理优劣。** 栈 vs 堆谁省事、谁不怕泄漏，这些是工程问题，卷面上没人问。卷面问的是"带头结点的插入/删除逻辑写对没有"。

4. **堆版本更能展示 malloc 判空**，而判空是标准采分点。

**唯一例外**：如果题目要求"写一个完整可运行的程序"（少见），栈头结点确实省事、不用管头结点的 free。
但看到这种题，也建议先把 `InitList` 写出来再决定放哪——因为**分数在算法，不在存储位置**。

---

## 六、考试模板（建议背下来）

```c
typedef int ElemType;

typedef struct LNode {
    ElemType data;
    struct LNode* next;
} LNode, *LinkList;              // 这个 typedef 组合是教材标准，务必记牢

// 建结点（内部工具，考试一般不用单独写）
LNode* BuyNode(ElemType e)
{
    LNode* p = (LNode*)malloc(sizeof(LNode));
    if (p == NULL) return NULL;
    p->data = e;
    p->next = NULL;
    return p;
}

// 初始化空表（这道题必考）
LinkList InitList(void)
{
    return BuyNode(0);
}

// 销毁（很多题要求"释放所有结点"）
void DestroyList(LinkList L)
{
    while (L != NULL) {
        LNode* next = L->next;
        free(L);
        L = next;
    }
}
```

### 两个提醒

- **不要在 C 考试里写 `&L`。** 教材伪代码的 `InitList(LinkList &L)` 是 **C++ 引用语法**。
  如果课程只教 C，阅卷会判语法错误。C 里就老老实实让 `InitList` 返回指针。
- **头结点加不加，比堆不堆更致命。** 考试 90% 的题默认"带头结点"。
  题目没明说时，写在注释里表个态：`/* 设链表带头结点 */`，这一步能救回不少分。

---

## 七、C 与 C++ 对照：构造函数就是 InitList

C++ 里"要不要写 InitList"这个问题被**构造函数**直接解决了：

```cpp
class SList {
public:
    SList() : head_{} { head_.next = nullptr; }   // 这就是 InitList，但编译器强制你调用
private:
    Node head_;
};
// 用法：SList L;   —— 不需要任何显式初始化调用
```

| 对比项 | C | C++ |
|---|---|---|
| 初始化靠什么 | `InitList` 函数，**约定** | 构造函数，**语言规则** |
| 忘了初始化会怎样 | 编译器不管，运行时才崩 | 编译不过 / 不可能忘 |
| 清理靠什么 | `DestroyList`，**约定** | 析构函数，**语言规则** |
| 头结点放哪 | 得手动选栈或堆 | 放成员变量（随对象走）或 `unique_ptr` |

这正是构造函数存在的理由：**在 C 里 `InitList` 是约定，忘了调用编译器不管；在 C++ 里它是语言规则，对象一旦诞生就必然完成初始化。**

> 学到「构造函数和析构函数」那一节时，可以把 `SList.c` 翻出来，按这个对照表改一遍。

---

## 八、易错点记录

- [ ] 混淆 `BuyNode` 与 `InitList` 的职责——它们都是"造结点"，区别是**造谁**（数据结点 vs 头结点）
- [ ] 以为"没写 `InitList`"就是"没初始化"——要看头结点是不是用声明语句直接建好了
- [ ] 在栈头结点的设计里漏写 `&`，导致改的是副本（注意：多数情况会编译报错，属幸运）
- [ ] 在 C 考试里照抄教材的 `InitList(LinkList &L)`——C 没有引用，语法错误
- [ ] 题目没说明时不写"设链表带头结点"的注释，白白丢分
- [ ] 堆头结点版本忘记 `DestroyList` 里连头结点一起 free

---

## 九、自测

1. 下面这段 `main`，如果 `InitList` 改成返回 `Node*`（堆头结点），需要动几行？

   ```c
   Node head = { 0, NULL };
   Node* tail = &head;
   /* ... 尾插 n 个结点 ... */
   ListInsert(&head, position, value);
   PrintList(&head);
   ClearList(&head);
   ```

   （提示：重点看那三个 `&`。改了之后，`tail` 的类型和初始化又该怎么写？）

2. 如果我想写一个函数 `Node* BuildListFromArray(int a[], int n)`，在函数里造好链表再返回给 `main`，
   栈头结点的写法能直接做到吗？为什么？

3. `PrintList(&head)` 为什么必须传地址？传 `PrintList(head)` 会发生什么？

---

## 附：相关文件

- 讨论的源文件：`e:\code\c++_learn\26_10_10\26_10_10\SList.c`（栈头结点写法，第 106 行）

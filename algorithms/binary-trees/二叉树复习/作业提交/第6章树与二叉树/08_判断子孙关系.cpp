#include <iostream>

bool Contains(const int* L, const int* R, int root, int target)
{
    if (root == 0)
    {
        return false;
    }
    if (root == target)
    {
        return true;
    }
    return Contains(L, R, L[root], target) ||
           Contains(L, R, R[root], target);
}

int main()
{
    int n;
    if (!(std::cin >> n) || n < 0)
    {
        return 0;
    }
    // 本题指定使用 L、R 两个数组存储左右孩子编号。
    int* L = new int[static_cast<std::size_t>(n) + 1];
    int* R = new int[static_cast<std::size_t>(n) + 1];
    L[0] = 0;
    R[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> L[i];
    }
    for (int i = 1; i <= n; i++)
    {
        std::cin >> R[i];
    }
    int u;
    int v;
    if (!(std::cin >> u >> v))
    {
        delete[] L;
        delete[] R;
        return 0;
    }
    bool result = false;
    if (u >= 1 && u <= n && v >= 1 && v <= n)
    {
        // 从 v 的孩子开始搜索，因此不将 v 本身算作其子孙。
        result = Contains(L, R, L[v], u) || Contains(L, R, R[v], u);
    }
    std::cout << (result ? 1 : 0) << '\n';
    delete[] L;
    delete[] R;
    return 0;
}

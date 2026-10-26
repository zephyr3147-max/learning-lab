#include <iostream>

int main()
{
    int n;
    if (!(std::cin >> n) || n < 0)
    {
        return 0;
    }
    // 题目明确要求顺序存储；下标从 1 开始，0 号位置表示无双亲。
    int* data = new int[static_cast<std::size_t>(n) + 1];
    data[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!(std::cin >> data[i]))
        {
            delete[] data;
            return 0;
        }
    }
    int x;
    if (!(std::cin >> x))
    {
        delete[] data;
        return 0;
    }
    int parent = 0;
    for (int i = 1; i <= n; i++)
    {
        if (data[i] != 0 && data[i] == x)
        {
            parent = data[i / 2];
            break;
        }
    }
    std::cout << parent << '\n';
    delete[] data;
    return 0;
}

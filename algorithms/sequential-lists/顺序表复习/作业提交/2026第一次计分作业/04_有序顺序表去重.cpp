#include <iostream>
#include <vector>

int main()
{
    int n;
    if (!(std::cin >> n) || n < 0)
    {
        std::cout << "0\n\n";
        return 0;
    }

    std::vector<int> values(static_cast<std::size_t>(n));
    for (int i = 0; i < n; ++i)
    {
        std::cin >> values[static_cast<std::size_t>(i)];
    }

    // 慢指针保存去重结果长度，快指针只读原有顺序表内容。
    int length = 0;
    for (int i = 0; i < n; ++i)
    {
        if (length == 0 ||
            values[static_cast<std::size_t>(i)] !=
                values[static_cast<std::size_t>(length - 1)])
        {
            values[static_cast<std::size_t>(length)] =
                values[static_cast<std::size_t>(i)];
            ++length;
        }
    }

    std::cout << length << '\n';
    for (int i = 0; i < length; ++i)
    {
        std::cout << (i == 0 ? "" : " ")
                  << values[static_cast<std::size_t>(i)];
    }
    std::cout << '\n';
    return 0;
}

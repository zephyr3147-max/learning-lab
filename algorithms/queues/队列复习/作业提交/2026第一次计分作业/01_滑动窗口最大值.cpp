#include <deque>
#include <iostream>
#include <vector>

int main()
{
    int n;
    int k;
    if (!(std::cin >> n >> k) || n <= 0 || k <= 0 || k > n)
    {
        std::cout << '\n';
        return 0;
    }

    std::vector<int> nums(static_cast<std::size_t>(n));
    for (int i = 0; i < n; ++i)
    {
        std::cin >> nums[static_cast<std::size_t>(i)];
    }

    // 队列保存下标，并保持对应数值从队头到队尾递减。
    std::deque<int> candidates;
    bool first = true;
    for (int i = 0; i < n; ++i)
    {
        // 移除已经离开当前窗口的下标。
        while (!candidates.empty() && candidates.front() <= i - k)
        {
            candidates.pop_front();
        }

        // 较小的旧值不可能成为后续窗口最大值。
        while (!candidates.empty() &&
               nums[static_cast<std::size_t>(candidates.back())] <=
                   nums[static_cast<std::size_t>(i)])
        {
            candidates.pop_back();
        }
        candidates.push_back(i);

        if (i >= k - 1)
        {
            std::cout << (first ? "" : " ")
                      << nums[static_cast<std::size_t>(candidates.front())];
            first = false;
        }
    }
    std::cout << '\n';
    return 0;
}

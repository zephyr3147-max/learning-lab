#include <iostream>
#include <stack>

int main()
{
    int n;
    if (!(std::cin >> n) || n < 0)
    {
        std::cout << "false\n";
        return 0;
    }

    std::stack<int> values;
    int nextToPush = 1;
    bool possible = true;

    for (int i = 0; i < n; ++i)
    {
        int wanted;
        std::cin >> wanted;
        if (wanted < 1 || wanted > n)
        {
            possible = false;
            continue;
        }

        // 依次压入尚未入栈的元素，直到栈顶可作为下一个出栈值。
        while (nextToPush <= n &&
               (values.empty() || values.top() < wanted))
        {
            values.push(nextToPush);
            ++nextToPush;
        }

        if (!values.empty() && values.top() == wanted)
        {
            values.pop();
        }
        else
        {
            possible = false;
        }
    }

    std::cout << (possible ? "true\n" : "false\n");
    return 0;
}

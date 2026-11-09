#include <iostream>
#include <vector>
#include <utility>
using namespace std;

void Print(const vector<int>& a)
{
    for (int i = 0; i < (int)a.size(); i++)
    {
        if (i > 0)
        {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
}

int main()
{
    int n;
    if (!(cin >> n))
    {
        return 0;
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int left = 0;
    int right = n - 1;
    while (left < right)
    {
        bool changed = false;
        for (int i = left; i < right; i++)
        {
            if (a[i] > a[i + 1])
            {
                swap(a[i], a[i + 1]);
                changed = true;
            }
        }
        right--;
        changed = false;
        for (int i = right; i > left; i--)
        {
            if (a[i - 1] > a[i])
            {
                swap(a[i - 1], a[i]);
                changed = true;
            }
        }
        left++;
        Print(a);
        if (!changed)
        {
            break;
        }
    }
    cout << "the new sort is:\n";
    Print(a);
    return 0;
}

#include <iostream>
#include <vector>
using namespace std;

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
    int low, high;
    cin >> low >> high;
    if (low > high)
    {
        return 0;
    }
    vector<int> number(high - low + 1, 0);
    for (int i = 0; i < n; i++)
    {
        if (a[i] < low || a[i] > high)
        {
            return 0;
        }
        number[a[i] - low]++;
    }
    bool first = true;
    for (int i = 0; i <= high - low; i++)
    {
        for (int j = 0; j < number[i]; j++)
        {
            if (!first)
            {
                cout << ' ';
            }
            cout << i + low;
            first = false;
        }
    }
    cout << '\n';
    return 0;
}

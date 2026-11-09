#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> a;
    int value;
    while (cin >> value)
    {
        a.push_back(value);
    }
    for (int gap = (int)a.size() / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < (int)a.size(); i++)
        {
            int key = a[i];
            int j = i;
            while (j >= gap && a[j - gap] > key)
            {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = key;
        }
    }
    for (int i = 0; i < (int)a.size(); i++)
    {
        if (i > 0)
        {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
    return 0;
}

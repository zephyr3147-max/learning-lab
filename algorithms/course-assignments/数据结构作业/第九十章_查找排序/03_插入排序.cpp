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
    for (int i = 1; i < (int)a.size(); i++)
    {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
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

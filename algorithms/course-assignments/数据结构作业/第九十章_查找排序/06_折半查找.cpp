#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string line;
    if (!getline(cin, line))
    {
        return 0;
    }
    istringstream input(line);
    vector<int> a;
    int value;
    while (input >> value)
    {
        a.push_back(value);
    }
    int key;
    if (!(cin >> key))
    {
        return 0;
    }
    int low = 0;
    int high = (int)a.size() - 1;
    vector<int> compared;
    bool found = false;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        compared.push_back(a[mid]);
        if (a[mid] == key)
        {
            found = true;
            break;
        }
        if (a[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    if (!found)
    {
        cout << "0\n";
        return 0;
    }
    for (int i = 0; i < (int)compared.size(); i++)
    {
        if (i > 0)
        {
            cout << ' ';
        }
        cout << compared[i];
    }
    cout << '\n';
    return 0;
}

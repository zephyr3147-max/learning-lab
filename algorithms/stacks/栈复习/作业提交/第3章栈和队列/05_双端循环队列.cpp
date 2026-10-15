#include <iostream>

int main()
{
    int count;
    if (!(std::cin >> count) || count <= 0)
    {
        return 0;
    }
    // This task explicitly requires sequential storage for its circular deque.
    int *deque = new int[count];
    int front = 0;
    int size = 0;
    for (int i = 0, value; i < count && std::cin >> value; ++i)
    {
        if (size == 0)
        {
            deque[front] = value;
            size = 1;
        }
        else
        {
            const int rear = (front + size - 1) % count;
            const long long endpointSum = static_cast<long long>(deque[front]) + deque[rear];
            if (2LL * value < endpointSum)
            {
                front = (front + count - 1) % count;
                deque[front] = value;
            }
            else
            {
                deque[(front + size) % count] = value;
            }
            ++size;
        }
    }
    for (int i = 0; i < size; ++i)
    {
        std::cout << (i == 0 ? "" : " ") << deque[(front + i) % count];
    }
    std::cout << '\n';
    delete[] deque;
    return 0;
}

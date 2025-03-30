
#include <iostream>

int partition(int* data, int left, int right)
{
    int basis = data[right - 1];

    int unpartited = 0;
    
    for (int i = 0; i < right - 1; ++i)
    {
        if (data[i] < basis)
        {
            std::swap(data[unpartited], data[i]);
            ++unpartited;
        }
    }

    std::swap(data[unpartited], data[right - 1]);

    return unpartited;
}

int main()
{
    int data[] = { 9, 7, 5, 4, 3, 2, 6 };
    int n = sizeof data / sizeof * data;
    int p = partition(data, 0, n);
    for (int i = 0; i < n; ++i)
    {
        std::cout << data[i] << std::endl;
    }
    std::cout << p << std::endl;
}

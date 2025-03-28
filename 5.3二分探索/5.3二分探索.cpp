#include <iostream>
#include <algorithm>
#include <numeric>

int* binary_serch(int* data, int n, int key)
{
    int l = 0;
    int r = n;

    while (l < r)
    {
        int mid = (l + r) / 2;
        if (key == data[mid])
            return data + mid;
        else if (key < data[mid])
            r = mid;
        else // if (key > data[mid])
            l = mid + 1;
    }
    return nullptr;
}

#include <vector>

int main()
{

    std::vector<int> data(100000);
    std::iota(data.begin(), data.end(), 1);
    
    if (int* found = binary_serch(data.data(), data.size(), 1230))
    {
        std::cout << "found data[" << std::distance(data.data(), found) << "] = " << *found << std::endl;
    }
    else
    {
        std::cout << "nod found" << std::endl;
    }
}

#include <algorithm>
#include <iostream>

static void bubble_sort(int* p, int n)
{
    int flag = 1;
    int i = 0;
    while (flag)
    {
        flag = 0;
        for (int j = n - 1; j >= i + 1; --j)
        {
            if (p[j] < p[j - 1])
            {
                std::swap(p[j], p[j - 1]);
                flag = 1;
            }
        }
        ++i;
    }
}
//static void bubble_sort(int* p, int n)
//{
//    for (int i = 0; i < n; ++i)
//    {
//        for (int j = n - 1; j > i; --j)
//        {
//            //std::cout << "J: " << j << "I: " << i << std::endl;
//            if (p[j] < p[j - 1])
//            {
//                std::swap(p[j], p[j - 1]);
//            }
//        }
//    }
//}

#include <iostream>

static void dump(int* p, int n)
{
    for (int i = 0; i < n; ++i)
    {
        if (i > 0) std::cout << " ";
        std::cout << p[i];
    }
    std::cout << std::endl;
}

int main()
{
    int data[] = { 5, 2, 4, 6, 1, 3 };
    int n = sizeof data / sizeof * data;
    bubble_sort(data, n);
    dump(data, n);
}

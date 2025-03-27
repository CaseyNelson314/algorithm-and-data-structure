// 挿入ソート
// [計算量] 
// - 最悪 O(N^2) 降順になっている場合
// - 最良 O(N)   昇順になっている場合
// [安定]
// - 離れた要素同士を交換することがないため


static void insert_sort(int* data, int n)
{
    for (int i = 1; i < n; ++i)
    {
        int v = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > v)
        {
            data[j + 1] = data[j];
            --j;
        }
        data[j + 1] = v;
    }
}

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
    insert_sort(data, n);
    dump(data, n);
}
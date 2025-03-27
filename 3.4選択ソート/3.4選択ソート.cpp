// 選択ソート
// [計算量] 
// - 最悪 O(N^2)
// - 最良 O(N^2)
// [不安定]
// - 離れた要素同士を交換するため。例えば [2a 4 2b 1] をソートする際に先頭の要素と最小値が交換され、[1 4 2b 2a] と順序が入れ替わる

#include <algorithm>
#include <iostream>

static void selection_sort(int* p, int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        int minj = i;
        for (int j = i; j < n; ++j)
        {
            if (p[j] < p[minj])
                minj = j;
        }
        std::swap(p[i], p[minj]);
    }
}

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
    selection_sort(data, n);
    dump(data, n);
}

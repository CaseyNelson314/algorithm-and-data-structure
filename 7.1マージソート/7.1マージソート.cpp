#include <iostream>
#include <vector>
#include <memory>

constexpr auto INF = 10000000000000;

void marge(int* data, int left, int mid, int right)
{
    int dl = mid - left;
    int dr = right - mid;

    auto l_buffer = std::unique_ptr<int[]>{ new int[dl + 1] };
    auto r_buffer = std::unique_ptr<int[]>{ new int[dr + 1] };

    // バッファにコピー
    for (int i = 0; i < dl; ++i)
    {
        l_buffer[i] = data[left + i];
    }

    for (int i = 0; i < dr; ++i)
    {
        r_buffer[i] = data[mid + i];
    }

    // 番兵
    l_buffer[dl] = INF;
    r_buffer[dr] = INF;

    int i = 0;
    int j = 0;

    for (int k = left; k < right; ++k)
    {
        if (l_buffer[i] < r_buffer[j])
        {
            data[k] = l_buffer[i];
            ++i;
        }
        else
        {
            data[k] = r_buffer[j];
            ++j;
        }
    }
}

void marge_sort(int* data, int left, int right)
{
    if (left + 1 == right) return;

    // 書籍での終了条件
    //if (left + 1 < right)
    //{
    int mid = (left + right) / 2;
    marge_sort(data, left, mid);
    marge_sort(data, mid, right);
    marge(data, left, mid, right);
    //}
}

int main()
{
    //std::vector<int> l{ 1, 3, 5 };
    //std::vector<int> r{ 2, 4, 6, 8, 10 };
    //auto m = marge(l, r);

    //for (auto& it : m)
    //{
    //    std::cout << it << std::endl;
    //}

    std::vector<int> data = { 1, 5, 2, 10, 3, 4, 7 };
    marge_sort(data.data(), 0, data.size());

    for (auto&& it : data)
    {
        std::cout << it << std::endl;
    }
}

#include <iostream>
#include <array>


struct Data {
    int uuid;
    int value;

    Data(int value)
        : value(value)
    {
        static int counter;
        uuid = counter;
        ++counter;
    }
};

// 選択ソート / 不安定ソート
static void selection_sort(Data* p, int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        int minj = i;
        for (int j = i; j < n; ++j)
        {
            if (p[j].value < p[minj].value)
                minj = j;
        }
        std::swap(p[i], p[minj]);
    }
}

// 挿入ソート / 安定ソート
static void insert_sort(Data* data, int n)
{
    for (int i = 1; i < n; ++i)
    {
        auto v = data[i];
        int j = i - 1;
        while (j >= 0 && data[j].value > v.value)
        {
            data[j + 1] = data[j];
            --j;
        }
        data[j + 1] = v;
    }
}

static void dump(Data* p, int n)
{
    for (int i = 0; i < n; ++i)
    {
        std::cout << p[i].value << " uuid: " << p[i].uuid << std::endl;
    }
    std::cout << std::endl;
}

// 安定、不安定判定
bool is_stable(Data* in, int n_in, Data* out, int n_out)
{
    for (int i = 0; i < n_in; ++i)
    {
        for (int j = i + 1; j < n_in; ++j)
        {
            for (int a = 0; a < n_out; ++a)
            {
                for (int b = a + 1; b < n_out; ++b)
                {
                    if (in[i].value == in[j].value &&
                        in[i].uuid == out[b].uuid &&
                        in[j].uuid == out[a].uuid)
                    {
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}

int main()
{
    {
        std::cout << "insert_sort" << std::endl;
        std::array<Data, 6> data{ 2, 2, 3, 6, 7, 1 };
        auto shuffled = data;
        dump(data.data(), data.size());
        insert_sort(data.data(), data.size());
        dump(data.data(), data.size());
        std::cout << "is stable : " << is_stable(data.data(), data.size(), shuffled.data(), shuffled.size()) << "\n\n";
    }

    {
        std::cout << "selection_sort" << std::endl;
        std::array<Data, 6> data{ 2, 2, 3, 6, 7, 1 };
        // 選択ソートは最小値を検索し、先頭から順にソートしていくため、
        // 最初に先頭の2と末尾の1がスワップされ2つの2の順序が入れ替わる。
        // そのため不安定ソート
 
        auto shuffled = data;
        dump(data.data(), data.size());
        selection_sort(data.data(), data.size());
        dump(data.data(), data.size());
        std::cout << "is stable : " << is_stable(data.data(), data.size(), shuffled.data(), shuffled.size()) << "\n\n";
    }
}
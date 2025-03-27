// 5.2線形探索.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <sstream>
#include <vector>

int* linear_serch(int* data, int n, int key)
{
    for (int i = 0; i < n; ++i)
    {
        if (data[i] == key)
            return data + i;
    }
    return nullptr;
}

int* sentry_linear_serch(int* data, int n, int key)
{
    for (int i = 0; ; ++i)
    {
        if (data[i] == key)
            return data + i;
    }
    return nullptr;  // unreachable
}

int main()
{
    using namespace std::string_literals;
    std::istringstream iss{ R"(5
1 2 3 4 5
3
3 4 1
)" };

    int n_src;
    iss >> n_src;
    std::vector<int> src;
    for (int i = 0; i < n_src; ++i)
    {
        int value;
        iss >> value;
        src.push_back(value);
    }

    int n_query;
    iss >> n_query;
    std::vector<int> query;
    for (int i = 0; i < n_query; ++i)
    {
        int value;
        iss >> value;
        query.push_back(value);
    }


    // 普通の線形探索
    {
        int n_found = 0;
        for (int i = 0; i < n_query; ++i)
        {
            if (int* found = linear_serch(src.data(), src.size(), query.at(i)))
            {
                ++n_found;
            }
        }
        std::cout << n_found << std::endl;
    }

    // 番兵を用いた線形探索
    {
        int n_found = 0;
        for (int i = 0; i < n_query; ++i)
        {
            int key = query.at(i);
            src.push_back(key);
            if (int* found = linear_serch(src.data(), src.size(), key))
            {
                ++n_found;
            }
        }
        std::cout << n_found << std::endl;
    }
}

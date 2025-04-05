#include <iostream>
#include <sstream>
#include <vector>

int main()
{
    using namespace std::string_literals;

    std::istringstream iss{ R"(5
7 8 1 2 3
)" };

    int n;
    iss >> n;

    std::vector<int> A(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        iss >> A[i];
    }

    // require print format
    // 
    // 子ノードを持つ場合
    // node {id}: key = {key}, left key = {key}, right key = {key}
    //
    // 子ノードが存在しない場合
    // node {id}: key = {key}

    // 完全二分木 (1オリジンの場合)
    // 右ノード = 2i+1
    // 左ノード = 2i
    // 親ノード = floor(i/2)

    auto right = [](int i) -> int { return 2 * i + 1;  };
    auto left = [](int i) -> int { return 2 * i;  };
    auto parent = [](int i) -> int { return std::floor(i / 2);  };

    auto in_range = [&](int i) -> bool { return 1 <= i && i <= n; };


    for (int i = 1; i <= n; ++i)
    {
        std::cout
            << "node " << i << ": "
            << "key = " << A[i];

        auto parent_index = parent(i);
        if (in_range(parent_index))
            std::cout << ", parent key = " << A[parent_index];

        auto left_index = left(i);
        if (in_range(left_index))
            std::cout << ", left key = " << A[left_index];

        auto right_index = right(i);
        if (in_range(right_index))
            std::cout << ", right key = " << A[right_index];

        std::cout << std::endl;
    }


}
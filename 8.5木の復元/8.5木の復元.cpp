// 先行順巡回で出力される数列と、中間順巡回で出力される数列が与えられるときに、
// 後行順巡回で出力される数列を求める問題 (山梨大学編入学試験で出題)

#include <iostream>
#include <sstream>
#include <vector>

struct Node
{
    int value;
    int right;
    int left;
};

Node node[100];

int main()
{
    using namespace std::string_literals;

    std::istringstream iss{ R"(9
1 2 3 4 5 6 7 8 9 
3 2 5 4 6 1 8 7 9
)" };

    int n;
    iss >> n;

    std::vector<int> preorder(n);
    std::vector<int> inorder(n);
    for (auto&& it : preorder)
        iss >> it;
    for (auto&& it : inorder)
        iss >> it;

    // 木を復元
    int pre_i = 0;

    auto solve = [&](auto self, int left, int right) -> int
        {
            if (left >= right)
                return -1;

            int parent_value = preorder[pre_i];
            pre_i++;

            //std::cout << "parent_value: " << parent_value << std::endl;

            auto pivot = std::find(inorder.cbegin(), inorder.cend(), parent_value);
            if (pivot == inorder.cend()) std::terminate();

            auto parent_i = std::distance(inorder.cbegin(), pivot);

            int left_i = self(self, left, parent_i);
            int right_i = self(self, parent_i + 1, right);

            node[parent_i].value = parent_value;
            node[parent_i].left = left_i;
            node[parent_i].right = right_i;

            return parent_i;
        };

    int root_i = solve(solve, 0, n);

    // 以降出力

    int depth = 0;

    auto visit = [&](auto self, int index) -> void
        {
            if (index == -1) return;

            std::fill_n(std::ostream_iterator<char>{ std::cout }, depth, ' ');
            std::cout << node[index].value << std::endl;

            depth++;
            self(self, node[index].left);
            depth--;

            depth++;
            self(self, node[index].right);
            depth--;
        };

    visit(visit, root_i);


    //3 4 2 5 1
}

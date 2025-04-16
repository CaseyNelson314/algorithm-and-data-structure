// むずすぎたのでスキップ

#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

int main()
{
    // req: 15125
    std::istringstream iss{ R"(6
30 35
35 15
15 5
5 10
10 20
20 25
)" };

    int n;
    iss >> n;

    std::vector<std::pair<int, int>> m(n);
    for (auto& it : m)
    {
        iss >> it.first >> it.second;
    }

    auto solve = [&](auto self, int left, int right) -> int
        {
            std::cout << "l: " << left << "r: " << right << std::endl;
            if (right - left == 2)
            {
                int left_row = m[left].first;
                int left_colom = m[left].second;
                int right_row = m[right - 1].second;
                std::cout << "return " << left_row * left_colom * right_row << std::endl;
                return left_row * left_colom * right_row;
            }

            for (int i = left + 2; i < right - 1; ++i)
            {
                std::cout << "left: " << left << " " << i << std::endl;
                std::cout << "right: " << i << " " << right << std::endl;
                int l = self(self, left, i);
                int r = self(self, i, right);
                return l + r;
                //return self(self, left, i) + self(self, i, right);
            }

            return 0;
        };

    int n_mul = solve(solve, 0, n);

    std::cout << n_mul << std::endl;
}

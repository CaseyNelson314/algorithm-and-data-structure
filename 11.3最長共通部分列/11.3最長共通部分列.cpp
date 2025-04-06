#include <iostream>
#include <sstream>
#include <vector>

int main()
{
    std::istringstream iss{ R"(
abcbdab
bdcaba
)" };

    std::string x;
    std::string y;
    iss >> x >> y;

    x = ' ' + x;
    y = ' ' + y;

    std::vector<std::vector<int>> c(y.size(), std::vector<int>(x.size()));

    for (int i = 1; i < y.size(); ++i)
    {
        for (int j = 1; j < x.size(); ++j)
        {
            if (x[i] == y[j])
                c[i][j] = c[i - 1][j - 1] + 1;
            else
                c[i][j] = std::max(c[i - 1][j], c[i][j - 1]);
        }
    }

    for (auto&& col : c)
    {
        for (auto&& v : col)
        {
            std::cout << v << ' ';
        }
        std::cout << std::endl;
    }

    std::cout << c[y.size() - 1][x.size() - 1] << std::endl;

}

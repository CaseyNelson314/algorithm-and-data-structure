
#include <iostream>
#include <sstream>
#include <vector>

struct Elem
{
    int area;
    bool use;
};

bool solve(std::vector<Elem>& data, int area, int n = 0)
{
    if (area == 0) return true;
    if (n == data.size() - 1) return false;

    // 選択する場合
    if (solve(data, area - data[n].area, n + 1))
    {
        data[n].use = true;
        return true;
    }

    // 選択しない場合
    if (solve(data, area, n + 1))
    {
        data[n].use = false;
        return true;
    }

    return false;

    //return solve(data, area - data[n].area, n + 1) or solve(data, area, n + 1);
}

int main()
{
    using namespace std::string_literals;

    std::istringstream iss{ R"(5
1 5 7 10 21
4
2 4 17 8)" };

    int n_A;
    iss >> n_A;

    std::vector<Elem> A;
    for (int i = 0; i < n_A; ++i)
    {
        int value;
        iss >> value;
        A.push_back({ value, false });
    }

    int n_query;
    iss >> n_query;
    for (int i = 0; i < n_query; ++i)
    {
        int query;
        iss >> query;

        std::cout << "query : " << query << std::endl;

        auto data = A;

        if (solve(data, query))
            std::cout << "yes" << std::endl;
        else
            std::cout << "no" << std::endl;

        for (auto& it : data)
        {
            std::cout << "area : " << it.area << " use: " << it.use << std::endl;
        }

        std::cout << std::endl;
    }
}

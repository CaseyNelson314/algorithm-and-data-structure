#include <iostream>
#include <tuple>
#include <vector>
#include <utility>
#include <type_traits>
#include <string>

void read_impl(std::istream& is, int rhs)
{
    is >> rhs;
}

template <typename T>
void read_impl(std::istream& is, std::vector<T>& rhs)
{
    int n;
    is >> n;

    rhs.resize(n);
    for (auto& it : rhs)
    {
        read_impl(is, it);
    }
}

template <typename T>
void read_impl(std::istream& is, std::vector<std::vector<T>>& rhs)
{
    int n;
    is >> n;

    rhs.resize(n);
    for (auto& row : rhs)
    {
        row.resize(n);
        for (auto& col : row)
        {
            read_impl(is, col);
        }
    }
}

template <typename F, typename S>
void read_impl(std::istream& is, std::pair<F, S>& rhs)
{
    read_impl(is, rhs.first);
    read_impl(is, rhs.second);
}

template <typename T>
T read(std::istream& is)
{
    T retval;
    read_impl(is, retval);
    return retval;
}

#include <sstream>

int main()
{
    using namespace std;
    istringstream iss{ R"(4
1 2 2 4
2 1 4
3 0
4 1 3
)" };

    auto q = read<vector<pair<int, vector<int>>>>(iss);
}

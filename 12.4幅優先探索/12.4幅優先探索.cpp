#include <iostream>
#include <sstream>
#include <vector>
#include <queue>


template <typename T>
T read(std::istream& is)
{
    T result;
    is >> result;
    return result;
}

int main()
{
    std::istringstream iss{ R"(4
1 2 2 4
2 1 4
3 0
4 1 3
)" };

    int n = read<int>(iss);

    std::vector<std::vector<int>> a(n, std::vector<int>(n));

    for (int i = 0; i < n; ++i)
    {
        int from = read<int>(iss) - 1;

        int nto = read<int>(iss);
        for (int j = 0; j < nto; ++j)
        {
            int to = read<int>(iss) - 1;
            a[from][to] = 1;
        }
    }

    int VISITED = -1;
    std::vector<int> color(n);
    std::vector<int> d(n);
    std::queue<int> q;

    q.push(0);

}
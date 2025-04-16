#include <iostream>
#include <sstream>
#include <vector>

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

    std::vector<std::vector<int>> g(n + 1, std::vector<int>(n + 1));

    for (int i = 0; i < n; ++i)
    {
        int from = read<int>(iss);
        int nout = read<int>(iss);

        for (int j = 0; j < nout; ++j)
        {
            int to = read<int>(iss);
            g[from][to] = 1;
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            std::cout << g[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

#include <iostream>
#include <sstream>
#include <vector>
#include <stack>

template <typename T>
T read(std::istream& is)
{
    T result;
    is >> result;
    return result;
}

int main()
{
    std::istringstream iss{ R"(6
1 2 2 3
2 2 3 4
3 1 5
4 1 6
5 1 6
6 0
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

    int time = 0;
    std::vector<int> visit_times(n);
    std::vector<int> leave_times(n);

    int VISITED = 1;
    std::vector<int> color(n);

    // 再帰を使ったDFS 
    auto dfs = [&](auto self, int curr) -> void
        {
            color[curr] = VISITED;
            visit_times[curr] = ++time;
            for (int i = 0; i < n; ++i)
            {
                if (a[curr][i] && color[i] != VISITED)
                {
                    self(self, i);
                }
            }
            leave_times[curr] = ++time;
        };
    dfs(dfs, 0);

    for (int i = 0; i < n; ++i)
    {
        std::cout << i + 1 << " " << visit_times[i] << " " << leave_times[i] << std::endl;
    }

    //for (auto&& row : a)
    //{
    //    for (auto&& col : row)
    //    {
    //        std::cout << col << " ";
    //    }
    //    std::cout << std::endl;
    //}

}

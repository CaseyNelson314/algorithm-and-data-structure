#include <iostream>
#include <queue>

template <typename T>
T read()
{
    T v;
    std::cin >> v;
    return v;
}

int main()
{
    std::priority_queue<int> pq;

    for (;;)
    {
        auto s = read<std::string>();

        if (s == "push")
        {
            pq.push(read<int>());
        }

        else if (s == "pop")
        {
            int max = pq.top();
            pq.pop();
            std::cout << max << std::endl;
        }

        else
        {
            std::cerr << "invali command" << std::endl;
        }
    }
}

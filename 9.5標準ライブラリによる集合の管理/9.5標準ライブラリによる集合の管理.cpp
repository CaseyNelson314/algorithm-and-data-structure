#include <iostream>
#include <string>
#include <set>

template <typename T>
T read()
{
    T v;
    std::cin >> v;
    return v;
}

int main()
{

    std::set<int> set;

    for (;;)
    {
        auto s = read<std::string>();

        if (s == "ins")
        {
            set.insert(read<int>());
        }

        else if (s == "del")
        {
            set.erase(read<int>());
        }

        else if (s == "find")
        {
            auto pos = set.find(read<int>());
            if (pos != set.end())
                std::cout << "found" << std::endl;
            else
                std::cout << "not found" << std::endl;
        }

        else if (s == "print")
        {
            for (auto&& it : set)
            {
                std::cout << it << std::endl;
            }
        }

        else
        {
            std::cout << "invalid command" << std::endl;
        }
    }
}


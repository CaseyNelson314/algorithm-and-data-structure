#include <iostream>
#include <sstream>
#include <vector>



int A[1024 + 1];

void insert(int key)
{
    int parent = std::floor(key / 2);
}

void extract()
{

}

template <typename T>
T read(std::istream& is)
{
    T v;
    is >> v;
    return v;
}

int main()
{
    std::istringstream iss{ R"(
insert 8
insert 2
extract
insert 10
extract
insert 11
extract
extract
end
)" };



    for (;;)
    {
        auto s = read<std::string>(iss);

        if (s == "end")
        {
            break;
        }

        if (s == "insert")
        {
            int v = read<int>(iss);
        }

        else if (s == "extract")
        {

        }

        else
        {
            std::cerr << "invalid command" << std::endl;
        }


    }
}

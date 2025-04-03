#include <iostream>
#include <sstream>

int NIL = -1;

struct Node
{
    int parent = NIL;
    int left = NIL;
    int right = NIL;
};

Node nodes[1024];

int depth(int i_node)
{
    int d = 0;
    while (nodes[i_node].parent != NIL)
    {
        i_node = nodes[i_node].parent;
        ++d;
    }
    return d;
}

std::string node_type(int i_node)
{
    if (nodes[i_node].left == NIL)
    {
        return "leaf []";
    }

    std::ostringstream oss;

    if (nodes[i_node].parent == NIL)
    {
        oss << "root [ ";
    }
    else
    {
        oss << "internal_node [ ";
    }

    oss << nodes[i_node].left << " ";

    int c = nodes[i_node].left;

    while (nodes[c].right != NIL)
    {
        oss << nodes[c].right << " ";
        c = nodes[c].right;
    }

    oss << "]";
    return oss.str();
}

int main()
{
    using namespace std::string_literals;

    std::istringstream iss{ R"(13
0 3 1 4 10
1 2 2 3
2 0
3 0
4 3 5 6 7
5 0
6 0
7 2 8 9
8 0
9 0 
10 2 11 12
11 0
12 0
)" };

    int n;
    iss >> n;

    for (int i = 0; i < n; ++i)
    {
        int i_node;
        int n_child;
        iss >> i_node >> n_child;

        int l;
        for (int j = 0; j < n_child; ++j)
        {
            int c;
            iss >> c;

            nodes[c].parent = i_node;

            if (j == 0)
            {
                nodes[i_node].left = c;
            }
            else
            {
                nodes[l].right = c;  // 右辺には線形リストを構築し挿入
            }
            l = c;
        }
    }

    for (int i = 0; i < n; ++i)
    {
        std::cout
            << "node: " << i << " "
            << "parent: " << nodes[i].parent << " "
            << "depth: " << depth(i) << " "
            << node_type(i)
            << std::endl;
    }
}

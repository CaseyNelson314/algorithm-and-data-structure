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

int get_sibling(int n_node)
{
    if (nodes[n_node].parent == NIL)
        return NIL;
    if (nodes[nodes[n_node].parent].left == n_node)
        return nodes[nodes[n_node].parent].right;
    if (nodes[nodes[n_node].parent].right == n_node)
        return nodes[nodes[n_node].parent].left;
    return NIL;
}

int get_degree(int n_node)
{
    return (nodes[n_node].left != NIL) + (nodes[n_node].right != NIL);
}

int get_depth(int n_node)
{
    int depth = 0;
    while (nodes[n_node].parent != NIL)
    {
        n_node = nodes[n_node].parent;
        ++depth;
    }
    return depth;
}

int get_height(int n_node)
{
    if (nodes[n_node].left == NIL && nodes[n_node].right == NIL)
        return 0;

    int left_height = get_height(nodes[n_node].left) + 1;
    int right_height = get_height(nodes[n_node].right) + 1;

    return std::max(left_height, right_height);
}

std::string get_node_type(int n_node)
{
    if (nodes[n_node].parent == NIL)
        return "root";
    
    if (nodes[n_node].left == NIL && nodes[n_node].right == NIL)
        return "leaf";

    return "internal node";
}

int main()
{
    using namespace std::string_literals;

    std::istringstream iss{ R"(9
0 1 4
1 2 3
2 -1 -1
3 -1 -1
4 5 8
5 6 7
6 -1 -1
7 -1 -1
8 -1 -1
)" };

    int n;
    iss >> n;

    for (int i = 0; i < n; ++i)
    {
        int i_node, left, right;
        iss >> i_node >> left >> right;

        nodes[i].left = left;
        nodes[i].right = right;

        if (left != NIL) nodes[left].parent = i;
        if (right != NIL) nodes[right].parent = i;
    }

    for (int i = 0; i < n; ++i)
    {
        std::cout
            << "node " << i << ": "
            << "parent = " << nodes[i].parent << " "
            << "sibling = " << get_sibling(i) << " "
            << "degree = " << get_degree(i) << " "
            << "depth = " << get_depth(i) << " "
            << "height = " << get_height(i) << " "
            << "nodetype = " << get_node_type(i) << std::endl;
    }
}

#include <iostream>
#include <sstream>

int NIL = -1;

struct Node
{
    int parent;
    int left;
    int right;
};

Node nodes[1024];

void preorder_parse(int i_node)
{
    if (i_node == NIL)
        return;

    std::cout << i_node << " ";
    preorder_parse(nodes[i_node].left);
    preorder_parse(nodes[i_node].right);
}

void inorder_parse(int i_node)
{
    if (i_node == NIL)
        return;

    inorder_parse(nodes[i_node].left);
    std::cout << i_node << " ";
    inorder_parse(nodes[i_node].right);
}

void postorder_parse(int i_node)
{
    if (i_node == NIL)
        return;

    postorder_parse(nodes[i_node].left);
    postorder_parse(nodes[i_node].right);
    std::cout << i_node << " ";
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

        nodes[i_node].left = left;
        nodes[i_node].right = right;

        if (left != NIL) nodes[left].parent = i_node;
        if (right != NIL) nodes[right].parent = i_node;
    }

    {
        std::cout << "preorder_parse" << std::endl;
        preorder_parse(0);
        std::cout << std::endl;
    }

    {
        std::cout << "inorder_parse" << std::endl;
        inorder_parse(0);
        std::cout << std::endl;
    }

    {
        std::cout << "postorder_parse" << std::endl;
        postorder_parse(0);
        std::cout << std::endl;
    }
}
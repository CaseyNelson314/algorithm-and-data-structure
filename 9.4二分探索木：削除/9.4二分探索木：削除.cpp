#include <iostream>
#include <sstream>

struct Node
{
    int key;
    Node* right;
    Node* left;
};

Node* root;

void insert(int key)
{
    if (not root)
    {
        root = new Node{ key, nullptr, nullptr };
        return;
    }

    Node* curr = root;
    for (;;)
    {
        if (key < curr->key)  // 挿入値が基準より小さい場合左側の枝に挿入
        {
            if (curr->left)
                curr = curr->left;
            else
            {
                curr->left = new Node{ key, nullptr, nullptr };
                break;
            }
        }
        else
        {
            if (curr->right)
                curr = curr->right;
            else
            {
                curr->right = new Node{ key, nullptr, nullptr };
                break;
            }
        }
    }
}

void preorder(Node* root)
{
    if (not root) return;

    static int depth;

    std::fill_n(std::ostream_iterator<char>{ std::cout }, depth, ' ');
    std::cout << root->key << std::endl;

    ++depth;
    preorder(root->left);
    --depth;

    ++depth;
    preorder(root->right);
    --depth;
}

void inorder(Node* root)
{
    if (not root) return;

    inorder(root->left);
    std::cout << root->key << ' ';
    inorder(root->right);
}

bool serch(Node* root, int key)
{
    if (not root)
        return false;

    if (key == root->key)
        return true;

    if (key < root->key)
        return serch(root->left, key);

    return serch(root->right, key);
}

void del(Node* root, int key)
{
    
}

int main()
{
    using namespace std::string_literals;

    std::istringstream iss{ R"(18
insert 8
insert 2
insert 3
insert 7
insert 22
insert 1
find 1
find 2
find 3
find 4
find 5
find 6
find 7
find 8
print
delete 3
delete 7
print
)" };

    int n;
    iss >> n;

    for (int i = 0; i < n; ++i)
    {
        std::string s;
        iss >> s;
        if (s == "insert")
        {
            int key;
            iss >> key;
            insert(key);
        }
        else if (s == "print")
        {
            std::cout << "inorder" << std::endl;
            inorder(root);
            std::cout << std::endl;

            std::cout << "preorder" << std::endl;
            preorder(root);
            std::cout << std::endl;
        }
        else if (s == "find")
        {
            int key;
            iss >> key;
            std::cout << (serch(root, key) ? "yes" : "no") << std::endl;
        }
        else if (s == "delete")
        {
            int key;
            iss >> key;
            del(root, key);
        }
    }
}

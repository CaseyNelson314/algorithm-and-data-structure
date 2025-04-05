#include <iostream>
#include <sstream>

struct Node
{
    int key;
    Node* parent;
    Node* right;
    Node* left;
};

Node* root = new Node{ -1, nullptr, nullptr, nullptr };  // NIL

void insert(int key)
{

    Node* curr = root;
    for (;;)
    {
        if (key < curr->key)  // 挿入値が基準より小さい場合左側の枝に挿入
        {
            if (curr->left)
                curr = curr->left;
            else
            {
                curr->left = new Node{ key, curr, nullptr, nullptr };
                break;
            }
        }
        else
        {
            if (curr->right)
                curr = curr->right;
            else
            {
                curr->right = new Node{ key, curr, nullptr, nullptr };
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

Node* find(Node* root, int key)
{
    if (not root)
        return nullptr;

    if (root->key == key)
        return root;

    if (key < root->key)
        return find(root->left, key);

    return find(root->right, key);
}

bool serch(Node* root, int key)
{
    return find(root, key);
}

void del(int key)
{
    Node* del_node = find(root, key);

    if (not del_node)
        return;

    // 削除対象が子を持たない場合、親ノードの管理下から切り離す
    if (not del_node->left && not del_node->right)
    {
        std::cout << "削除対象が子を持たない場合" << std::endl;
        if (del_node->parent->right == del_node)
            del_node->parent->right = nullptr;
        else if (del_node->parent->left == del_node)
            del_node->parent->left = nullptr;
        delete del_node;
        return;
    }

    // 削除対象が1つの子を持つ場合、削除対象の親と、削除対象の子を接続する
    if (del_node->left && not del_node->right)
    {
        std::cout << "削除対象が左のみに子を持つ場合" << std::endl;
        if (del_node->parent->right == del_node)
            del_node->parent->right = del_node->left;
        else if (del_node->parent->left == del_node)
            del_node->parent->left = del_node->left;
        del_node->left->parent = del_node->parent;
        delete del_node;
        return;
    }

    // 削除対象が1つの子を持つ場合、削除対象の親と、削除対象の子を接続する
    if (not del_node->left && del_node->right)
    {
        std::cout << "削除対象が右のみに子を持つ場合" << std::endl;
        if (del_node->parent->right == del_node)
        {
            del_node->parent->right = del_node->right;
        }
        else if (del_node->parent->left == del_node)
        {
            del_node->parent->left = del_node->right;
        }
        del_node->right->parent = del_node->parent;
        delete del_node;
        return;
    }


    std::cout << "削除対象が左右に子を持つ場合" << std::endl;

    // 削除対象が2つの子を持つ場合、削除対象の右の子を親としたときの最小値ノードを昇格する。
    // つまり削除対象の右の子から見て一番左側のノードを昇格させる
    Node* min_node = del_node->right;
    while (min_node->left)
    {
        min_node = min_node->left;
    }

    // 最小値ノードの親の管理下から切断
    if (min_node->parent->left == min_node)
        min_node->parent->left = nullptr;
    else if (min_node->parent->right == min_node)
        min_node->parent->right = nullptr;

    // 削除対象と右の最小値ノードを入れ替える
    min_node->left = del_node->left;
    min_node->right = del_node->right;
    min_node->parent = del_node->parent;
    if (del_node->parent->left == del_node)
        del_node->parent->left = min_node;
    else if (del_node->parent->right == del_node)
        del_node->parent->right = min_node;
    delete del_node;
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

    //auto& iss = std::cin;

    int n;
    iss >> n;

    for (int i = 0; i < n; ++i)
        //for (;;)
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
            //std::cout << "inorder" << std::endl;
            //inorder(root);
            //std::cout << std::endl;

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
            del(key);
        }
        else
        {
            std::cout << "invalid command" << std::endl;
        }
    }
}

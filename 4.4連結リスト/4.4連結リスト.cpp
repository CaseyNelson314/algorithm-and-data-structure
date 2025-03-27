struct Node
{
    int value;
    Node* next;
    Node* prev;
};

Node* nil;

void init()
{
    nil = new Node();
    nil->next = nil;
    nil->prev = nil;
}

// 先頭に挿入
void insert(int value)
{
    Node* new_node = new Node();
    new_node->value = value;

    // [nil] [new_node] [node] ...
    // 書き換えるもの nil->next, node->prev, new_node->next, new_node->prev
    // 以下4行の実行順序に注意
    new_node->next = nil->next;
    nil->next->prev = new_node;  // node->prev 最初はnil->next==nilなので、nil->next=new_nodeとなる
    nil->next = new_node;
    new_node->prev = nil;
}

Node* serch(int value)
{
    for (Node* curr = nil->next; curr != nil; curr = curr->next)
    {
        if (curr->value == value)
        {
            return curr;
        }
    }
    return nullptr;
}

void del(Node* node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;
    delete node;
}

void del_first()
{
    del(nil->next);
}

void del_last()
{
    del(nil->prev);
}

#include <iostream>

void dump()
{
    for (Node* curr = nil->next; curr != nil; curr = curr->next)
    {
        std::cout << curr->value << " ";
    }
    std::cout << std::endl;
}

#include <sstream>

int main()
{
    using namespace std::string_literals;

    std::istringstream iss{ R"(7
insert 5
insert 2
insert 3
insert 1
delete 3
insert 6
delete 5
)"s };

    int n_command;
    iss >> n_command;

    init();

    for (int i = 0; i < n_command; ++i)
    {
        std::string command;
        iss >> command;

        if (command == "insert")
        {
            int value;
            iss >> value;
            insert(value);
        }

        if (command == "delete")
        {
            int value;
            iss >> value;
            del(serch(value));
        }
    }

    dump();
}

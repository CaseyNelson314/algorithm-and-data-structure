#include <iostream>
#include <sstream>
#include <vector>



int A[1024 + 1];
int size;

void insert(int key)
{
    ++size;
    A[size] = key;  // 最深部に新規値を挿入

    auto parent = [](int i) -> int { return std::floor(i / 2);  };

    // 親まで木を上り、各親と挿入値を比較、挿入値の方が大きければ親に昇格
    int curr = size;
    while (curr > 1 && A[parent(curr)] < A[curr])
    {
        std::swap(A[parent(curr)], A[curr]);
        curr = parent(curr);
    }
}

void preorder(int i)
{
    if (1 <= i && i <= size)
    {
        int left = i * 2;
        int right = i * 2 + 1;

        static int depth;

        std::fill_n(std::ostream_iterator<char>{ std::cout }, depth, ' ');
        std::cout << A[i] << std::endl;

        depth++;
        preorder(left);
        preorder(right);
        depth--;

    }
}

int extract()
{
    if (size < 1) return -1;

    int max = A[1];  // 先頭は必ず最大値

    int min = A[size];  // 末尾は必ず最小値

    size--;

    // 先頭を最小値とし、最大ヒープ化
    A[1] = min;

    auto max_heapify = [&](auto self, int curr) -> void
        {
            int left = curr * 2;
            int right = curr * 2 + 1;

            int largest = curr;
            if (left <= size && A[left] > A[largest])
                largest = left;
            if (right <= size && A[right] > A[largest])
                largest = right;

            if (A[largest] != A[curr])
            {
                std::swap(A[largest], A[curr]);  // 左右どちらかの木の最大ヒープ構造が壊れたので、壊れた木に対して再度最大ヒープ化
                self(self, largest);
            }
        };

    for (int i = size; i >= 1; --i)
    {
        max_heapify(max_heapify, i);
    }

    return max;
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

    //auto& iss = std::cin;



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
            insert(v);
        }

        else if (s == "extract")
        {
            int max = extract();
            std::cout << max << std::endl;
        }

        else if (s == "print")
        {
            preorder(1);
        }

        else
        {
            std::cerr << "invalid command" << std::endl;
        }


    }
}

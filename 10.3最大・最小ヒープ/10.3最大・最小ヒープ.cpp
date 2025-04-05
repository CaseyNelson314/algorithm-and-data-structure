#include <iostream>
#include <sstream>
#include <vector>


int main()
{
    // input:
    // 10
    // 4 1 3 2 16 9 10 14 8 7
    // req:
    // 16 14 10 8 7 9 3 2 4 1

    using namespace std::string_literals;

    std::istringstream iss{ R"(10
4 1 3 2 16 9 10 14 8 7
)" };

    int n;
    iss >> n;

    std::vector<int> A(n + 1);
    for (int i = 1; i <= n; ++i)
        iss >> A[i];

    auto max_heapify = [&](auto self, int curr) -> void
        {
            int left = curr * 2;
            int right = curr * 2 + 1;

            // 親、左右の子の中で最大のノードを選択する
            int largest = curr;
            if (left <= n && A[left] > A[largest])
                largest = left;
            if (right <= n && A[right] > A[largest])
                largest = right;

            // 親が最大の場合はすでに最大ヒープになっているので何もしない
            if (largest == curr) return;

            std::swap(A[curr], A[largest]);
            self(self, largest);  // スワップによって左側の最大ヒープ構造が壊れたので再構築
        };

    for (int i = n / 2; i >= 1; --i)
    {
        max_heapify(max_heapify, i);
    }

    for (int i = 1; i <= n; ++i)
    {
        std::cout << A[i] << " ";
    }

    std::cout << std::endl;
}

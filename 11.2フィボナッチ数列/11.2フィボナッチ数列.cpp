#include <iostream>
#include <vector>
#include <chrono>

template <typename Visitor>
void m(Visitor visitor)
{
    auto start = std::chrono::system_clock::now();

    visitor();

    auto finish = std::chrono::system_clock::now();

    std::cout << "t(ns): " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << std::endl;
}

int main()
{
    constexpr auto n_fib = 40;

    m([&]
        {
            auto fibonacci = [&](auto self, int n) -> int
                {
                    if (n == 0 || n == 1) return 1;
                    return self(self, n - 1) + self(self, n - 2);
                };

            std::cout << fibonacci(fibonacci, n_fib) << std::endl;
        });

    // 動的計画法を適用したフィボナッチ数列計算機
    m([&]
        {
            auto dq_fibonacci = [&](auto self, int n) -> int
                {
                    static int memo[n_fib];

                    if (n == 0 || n == 1)
                    {
                        return memo[n] = 1;
                    }

                    if (memo[n])
                        return memo[n];

                    return memo[n] = self(self, n - 1) + self(self, n - 2);
                };

            std::cout << dq_fibonacci(dq_fibonacci, n_fib) << std::endl;
        });

    // 動的計画法を適用したフィボナッチ数列計算機 (関数呼び出し展開バージョン)
    // 関数呼び出しの方と比較したが、処理時間に大差なかった
    m([&]
        {
            auto dq_fibonacci = [&](int n) -> int
                {
                    static int memo[n_fib];

                    memo[0] = 1;
                    memo[1] = 1;

                    for (int i = 2; i <= n; ++i)
                    {
                        memo[i] = memo[i - 1] + memo[i - 2];
                    }

                    return memo[n];
                };

            std::cout << dq_fibonacci(n_fib) << std::endl;
        });
}

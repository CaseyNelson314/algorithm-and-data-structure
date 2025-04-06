// 6.2の全探索のコードをメモ化を用いて高速化

#include <iostream>
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
    constexpr int parts[] = { 1, 5, 7, 10, 21, 12, 10, 4, 123, 455, 102, 302, 200, 20, 1, 5, 7, 10, 21,1, 5, 7, 10, 21, 12, 10, 4 };
    constexpr int area = 1386;
    constexpr int n = sizeof parts / sizeof * parts;

    m([&]
        {
            auto fillable = [&](auto self, int i, int remain) -> bool
                {
                    if (remain == 0) return true;
                    if (i >= n) return false;

                    return self(self, i + 1, remain) || self(self, i + 1, remain - parts[i]);
                };

            std::cout << (fillable(fillable, 0, area) ? "yes" : "no") << std::endl;
        });


    m([&]
        {
            auto dq_fillable = [&](auto self, int i, int remain) -> int
                {
                    static int memo[n + 1][area];  // cannot: -1, can: 1, unknown 0

                    // 既に計算済みの場合
                    if (memo[i][remain] != 0)
                        return memo[i][remain];

                    if (remain == 0)
                        return memo[i][remain] = 1;

                    if (i >= n)
                        return memo[i][remain] = -1;

                    if (self(self, i + 1, remain) == 1)
                        return memo[i][remain] = 1;

                    if (self(self, i + 1, remain - parts[i]) == 1)
                        return memo[i][remain] = 1;

                    return memo[i][remain];
                };

            int can = dq_fillable(dq_fillable, 0, area);
            std::cout << "dq : " << can << std::endl;

        });
}

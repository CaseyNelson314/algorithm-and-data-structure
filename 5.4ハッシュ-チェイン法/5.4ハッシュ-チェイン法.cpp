// チェイン法を用いたハッシュテーブルの簡易実装
// 
// チェイン法はハッシュテーブルの各要素がリストを持っており、ハッシュ値が衝突した際はリストに追加するような方法
//
// オープンアドレス法と比較したときのメリット
//  要素を削除する処理が描きやすい STLのハッシュテーブルもこれ


#include <iostream>
#include <vector>

struct Bucket
{
    std::string key;
    int value;
    Bucket* next;
};

size_t hash(std::string key)
{
    return std::hash<std::string>{}(key);
}


constexpr size_t n_bucket = 100000;

Bucket buckets[n_bucket];

void insert(std::string key, int value)
{
    auto& f_bucket = buckets[hash(key) % n_bucket];

    Bucket* new_bucket = new Bucket{ key, value, nullptr };

    Bucket* it = &f_bucket;
    while (it->next)
    {
        it = it->next;
    }
    it->next = new_bucket;
}

int find(std::string key)
{
    auto& f_bucket = buckets[hash(key) % n_bucket];

    for (Bucket* it = &f_bucket; it; it = it->next)
    {
        if (it->key == key)
        {
            return it->value;
        }
    }

    return -1;
}

int main()
{
    for (int i = 0; i < 10000; ++i)
    {
        insert(std::string{ char(i) }, i);
    }

    for (int i = 0; i < 10000; ++i)
    {
        int value = find(std::string{ char(i) });
        //if (value != -1)
        //    std::cout << value << std::endl;
    }
}

// オープンアドレス法を用いたハッシュテーブルの簡易実装
// 
// オープンアドレス法はハッシュ値が衝突した際に挿入位置を再計算するという方法である
// [デメリット] 削除時の処理が面倒：キーが衝突した要素同士は連続、もしくは特定の規則の順に並んでいないと検索失敗するため、削除時に要素を削除するだけでは不十分。削除時には要素を削除するのではなく、NIL等のフラグを立て、連続性を保つ必要がある
// 
// 再計算の方法は主に、線形探索、二次探索、二重ハッシュがある。
// - 線形探索
//   衝突時にハッシュ値+iの要素へ挿入する方法 hash(key, i) = f(key) + i (i=0; i<size; ++i)
//   [メリット] 要素を削除しない場合実装が楽。ただ二次探索も十分に楽なのでよろしくない
//   [デメリット] データがハッシュテーブルの特定の領域に偏りがち(クラスタリング)：ハッシュ値が衝突しやすくなる
//              
// - 二次探索
//   衝突時にハッシュ値+i*iの要素へ挿入する方法 hash(key, i) = f(key) + i*i  (i=0; i<size; ++i)
//   [メリット] クラスタリングが起きにくい、実装が楽
//   [デメリット] 
// 
// - 二重ハッシュ
//   衝突時に他のハッシュ関数を用いて挿入位置を計算する方法 hash(key, i) = f(key) + i*g(key)  (i=0; i<size; ++i)
//   [メリット] クラスタリングが起きにくい
//   [デメリット] g(x)は単純な実装にする必要がある 
// 

#include <string>
#include <iostream>

constexpr int n_bucket = 1000;

struct Bucket
{
    std::string key;
    int value;
    bool used;
};

Bucket buckets[n_bucket];

size_t hash(std::string key)
{
    return std::hash<std::string>{}(key);
}

int n_confrict;

void insert(std::string key, int value)
{
    size_t h = hash(key);

    for (size_t i = 0; i < n_bucket; ++i)
    {
        size_t norm_h = (h + i * i) % n_bucket;

        auto& f_bucket = buckets[norm_h];

        if (not f_bucket.used)
        {
            f_bucket.key = key;
            f_bucket.value = value;
            f_bucket.used = true;
            return;
        }
        else
        {
            //std::cout << "衝突" << std::endl;
            ++n_confrict;
        }
    }
    std::cout << "挿入失敗" << std::endl;
}


int find(std::string key)
{
    size_t h = hash(key);

    for (size_t i = 0; i < n_bucket; ++i)
    {
        size_t norm_h = (h + i * i) % n_bucket;

        auto& f_bucket = buckets[norm_h];

        if (f_bucket.key == key)
            return f_bucket.value;
    }

    return -1;
}

#include <chrono>

int main()
{
    for (int i = 0; i < 800; ++i)
    {
        insert(std::string{ char(i) }, i);
    }

    std::cout << "n_confrict: " << n_confrict << std::endl;

    //for (int i = 0; i < 1000; ++i)
    //{
    //    int value = find(std::string{ char(i) });
    //    if (value != -1)
    //        std::cout << value << std::endl;
    //}


}


// 本で紹介されているやつ
//#include <stdlib.h>
//#include <string.h>
//
//constexpr int n_buffer = 1024;
//constexpr int n_char = 10;
//
////struct Bucket
////{
////
////};
//
//char buffer[n_buffer][n_char];
//
//int hash(const char* string)
//{
//    int hash = 0;
//    while (*string)
//    {
//        hash += *string;
//        ++string;
//    }
//    return hash;
//}
//
//void insert(const char* string)
//{
//    strncpy_s(buffer[hash(string)], string, strlen(string));
//}
//
//int find(const char* string)
//{
//    if (strcmp(buffer[hash(string)], string) == 0)
//    {
//        return 0;
//    }
//    else
//    {
//        return 1;
//    }
//}
//
//#include <iostream>
//#include <sstream>
//
//int main()
//{
//    using namespace std::string_literals;
//
//    std::istringstream iss{
//        R"(6
//insert AAA
//insert AAC
//find AAA
//find CCC
//insert CCC
//find CCC
//)"
//    };
//
//    int n_command;
//    iss >> n_command;
//
//    for (int i = 0; i < n_command; ++i)
//    {
//        std::string command;
//        std::string value;
//        iss >> command >> value;
//        if (command == "insert")
//            insert(value.c_str());
//        if (command == "find")
//            if (find(value.c_str()) == 0)
//                std::cout << "yes" << std::endl;
//            else
//                std::cout << "no" << std::endl;
//    }
//
//    //yes no
//
//}

#include "vector.hpp"
#include <sstream>
#include <iostream>

int main(void)
{
    // std::vector<int> stl;
    // ft::vector<int> ft;
    
    // size_t size = 10;
    // int value = 5;
    // std::vector<int> stl2(size, value);
    // ft::vector<int> ft2(size, value);
    
    // std::stringstream ss;
    // std::stringstream ss2;
    // ss << 1 << 2 << 3;
    // ss2 << 1 << 2 << 3;
    // std::istream_iterator<int> it_stl(ss);
    // std::istream_iterator<int> it_ft(ss2);
    // std::istream_iterator<int> ite;
    // ft::vector<int> ft3(it_ft, ite);
    // std::vector<int> stl3(it_stl, ite);
    
    // size = 10;
    // value = 5;
    // ft::vector<int> for_copy(size, value);
    // ft::vector<int> ft4(for_copy);
    
    // ft3 = for_copy;

    // // //
    // size = 3;
    // value = 5;
    // size_t cap = 5;
    // ft::vector<int> target(size, value);
    // target.reserve(cap); // leakなし
    
    // // capより大きいケース
    // size_t next_size = 7;
    // int next_value = 10;
    // target.assign(next_size, next_value);
    
    // // sizeより大きいケース
    // size_t next_cap = 10;
    // target.reserve(next_cap);
    // next_size = 8;
    // target.assign(next_size, next_value);
    
    // // sizeより小さいケース
    // next_size = 3;
    // target.assign(next_size, next_value);
   
    size_t size = 3;
    long value = 10;
    std::vector<long> stl(size, value);
    ft::vector<long> ft(size, value);
    
    size_t cap = 7;
    
    stl.reserve(cap);
    ft.reserve(cap);
    // 1.capがある場合
    // 終端に挿入
    stl.insert(stl.end(), 1);
    ft.insert(ft.end(), 1);

    // それ以外
    std::vector<long>::iterator stl_it = stl.begin();
    ft::vector<long>::iterator ft_it = ft.begin();
    stl_it += 2;
    ft_it += 2;

    stl.insert(stl_it, 1);
    ft.insert(ft_it, 1);
    
    // 2.capがない場合
    stl.resize(3, 3); 
    ft.resize(3, 3);
    stl.insert(stl.end(), 1);
    ft.insert(ft.end(), 1);
    system("leaks a.out"); 
}

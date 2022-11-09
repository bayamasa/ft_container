#include "vector.hpp"
#include <sstream>

int main(void)
{
    std::vector<int> stl;
    ft::vector<int> ft;
    
    size_t size = 10;
    int value = 5;
    std::vector<int> stl2(size, value);
    ft::vector<int> ft2(size, value);
    
    std::stringstream ss;
    std::stringstream ss2;
    ss << 1 << 2 << 3;
    ss2 << 1 << 2 << 3;
    std::istream_iterator<int> it_stl(ss);
    std::istream_iterator<int> it_ft(ss2);
    std::istream_iterator<int> ite;
    ft::vector<int> ft3(it_ft, ite);
    std::vector<int> stl3(it_stl, ite);
    
    size = 10;
    value = 5;
    ft::vector<int> for_copy(size, value);
    ft::vector<int> ft4(for_copy);

    // //
    size = 3;
    value = 5;
    size_t cap = 5;
    ft::vector<int> target(size, value);
    target.reserve(cap); // leakなし
    
    // capより大きいケース
    size_t next_size = 7;
    int next_value = 10;
    target.assign(next_size, next_value);
    
    // sizeより大きいケース
    size_t next_cap = 10;
    target.reserve(next_cap);
    next_size = 8;
    target.assign(next_size, next_value);
    
    // sizeより小さいケース
    next_size = 3;
    target.assign(next_size, next_value);
    system("leaks a.out"); 
    
}

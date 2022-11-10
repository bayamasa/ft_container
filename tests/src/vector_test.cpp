#include "vector.hpp"

#include <vector>
#include <iostream>
#include <iterator>
#include <sstream>
#include <gtest/gtest.h>
#include <string>

template <typename T, typename Allocator>
void debug_print(std::vector<T, Allocator>& stl, ft::vector<T, Allocator>& ft)
{
  std::cout << "stl size: " << stl.size() << std::endl;
  std::cout << "ft size: " << ft.size() << std::endl;
  std::cout << "stl max size: " << stl.max_size() << std::endl;
  std::cout << "ft max size: " << ft.max_size() << std::endl;
  typename std::vector<T, Allocator>::iterator stl_it = stl.begin();
  typename ft::vector<T, Allocator>::iterator ft_it = ft.begin();

  while (stl_it != stl.end()) {
    std::cout << "stl value: " << *stl_it++ << std::endl;
    std::cout << "ft value: " << *ft_it++ << std::endl;
  }
}

template <typename T, typename Allocator>
void expect_eq_stl_to_ft(std::vector<T, Allocator>& stl, ft::vector<T, Allocator>& ft) {
  typename std::vector<T, Allocator>::iterator stl_it = stl.begin();
  typename ft::vector<T, Allocator>::iterator ft_it = ft.begin();

  while (stl_it != stl.end()) {
    EXPECT_EQ(*stl_it++, *ft_it++);
  }
  EXPECT_TRUE(ft_it == ft.end());
  EXPECT_EQ(stl.size(), ft.size());
  EXPECT_EQ(stl.max_size(), ft.max_size());
  EXPECT_EQ(stl.empty(), ft.empty());
}

template <typename T, typename Allocator>
void expect_eq_ft(ft::vector<T, Allocator>& ft_1, ft::vector<T, Allocator>& ft_2) {
  typename ft::vector<T, Allocator>::iterator ft_it_1 = ft_1.begin();
  typename ft::vector<T, Allocator>::iterator ft_it_2 = ft_2.begin();

  while (ft_it_1 != ft_1.end()) {
    EXPECT_EQ(*ft_it_1++, *ft_it_2++);
  }
  EXPECT_TRUE(ft_it_2 == ft_2.end());
  EXPECT_EQ(ft_1.size(), ft_2.size());
  EXPECT_EQ(ft_1.max_size(), ft_2.max_size());
  EXPECT_EQ(ft_1.empty(), ft_2.empty());
  EXPECT_EQ(ft_1.capacity(), ft_2.capacity());
}

template <typename T, typename Allocator>
void expect_size_value_cap(ft::vector<T, Allocator>&ft, size_t size, T value, size_t cap)
{
  typename ft::vector<T, Allocator>::iterator itr = ft.begin();
  EXPECT_EQ(ft.size(), size);
  EXPECT_EQ(ft.capacity(), cap);
  while (itr != ft.end()) {
    EXPECT_EQ(*itr++, value);
  }
}

TEST(Vector, DefaultConstructor) {
    std::vector<int> stl;
    ft::vector<int> ft;
    expect_eq_stl_to_ft(stl, ft);
}

TEST(Vector, FillConstructor) {
    size_t size = 10;
    int value = 5;
    std::vector<int> stl(size, value);
    ft::vector<int> ft(size, value);
    
    expect_eq_stl_to_ft(stl, ft);
}

TEST(Vector, RangeConstructor_InputIterator) {
    std::stringstream ss;
    std::stringstream ss2;
    ss << 1 << 2 << 3;
    ss2 << 1 << 2 << 3;
    std::istream_iterator<int> it_stl(ss);
    std::istream_iterator<int> it_ft(ss2);
    std::istream_iterator<int> ite;
    ft::vector<int> ft(it_ft, ite);
    std::vector<int> stl(it_stl, ite);

    expect_eq_stl_to_ft(stl, ft);
}

TEST(Vector, RangeConstructor_ForwardIterator) {
    size_t size = 10;
    int value = 5;
    std::vector<int> for_iter(size, value);

    std::vector<int>::iterator it_ft = for_iter.begin();
    std::vector<int>::iterator it_stl = for_iter.begin();
    std::vector<int>::iterator it_end = for_iter.end();
  
    ft::vector<int> ft(it_ft, it_end);
    std::vector<int> stl(it_stl, it_end);
    
    expect_eq_stl_to_ft(stl, ft);
}


TEST(Vector, CopyConstructor) {
    size_t size = 10;
    int value = 5;
    ft::vector<int> for_copy(size, value);
    ft::vector<int> ft(for_copy);
    expect_eq_ft(for_copy, ft);
}

TEST(Vector, AssignedOperator) {
    size_t size = 10;
    int value = 5;
    ft::vector<int> for_copy(size, value);
    ft::vector<int> ft = for_copy;
    expect_eq_ft(for_copy, ft);
    
    size = 5;
    value = 10;
    ft::vector<int> ft2(size, value);
    ft2 = for_copy;
    expect_eq_ft(for_copy, ft2);
}

TEST(Vector, Begin) {
    int value = 1;
    int value2 = 2;
    ft::vector<int> ft;
    ft.push_back(value);
    ft.push_back(value2);
    ft::vector<int>::iterator itr = ft.begin();
    ft::vector<int>::const_iterator citr = ft.begin();
    EXPECT_EQ(*itr, value);
    EXPECT_EQ(*citr, value);
}

TEST(Vector, Rend) {
    int value = 1;
    int value2 = 2;
    ft::vector<int> ft;
    ft.push_back(value);
    ft.push_back(value2);
    ft::vector<int>::reverse_iterator itr = ft.rend();
    ft::vector<int>::const_reverse_iterator citr = ft.rend();
    EXPECT_EQ(*itr, value);
    EXPECT_EQ(*citr, value);
}

TEST(Vector, End) {
    int value = 1;
    int value2 = 2;
    ft::vector<int> ft;
    ft.push_back(value);
    ft.push_back(value2);
    ft::vector<int>::iterator itr = ft.end();
    ft::vector<int>::const_iterator citr = ft.end();
    EXPECT_EQ(*(--itr), value2);
    EXPECT_EQ(*(--citr), value2);
}

TEST(Vector, Rbegin) {
    int value = 1;
    int value2 = 2;
    ft::vector<int> ft;
    ft.push_back(value);
    ft.push_back(value2);
    ft::vector<int>::reverse_iterator itr = ft.rbegin();
    ft::vector<int>::const_reverse_iterator citr = ft.rbegin();
    EXPECT_EQ(*(++itr), value2);
    EXPECT_EQ(*(++citr), value2);
}

TEST(Vector, resize) {
    size_t size = 3;
    long value = 10;
    std::vector<long> stl(3, 10);
    ft::vector<long> ft(3, 10);
    
    // 引数1つ
    stl.resize(4);
    ft.resize(4);
    expect_eq_stl_to_ft(stl, ft);
    
    // 縮小
    stl.resize(2, 5);
    ft.resize(2, 5);
    expect_eq_stl_to_ft(stl, ft);
    
    // 拡大
    stl.resize(10, 100);
    ft.resize(10, 100);
    expect_eq_stl_to_ft(stl, ft);
    
    // 同じ要素, サイズ
    stl.resize(10, 100);
    ft.resize(10, 100);
    expect_eq_stl_to_ft(stl, ft);
}


TEST(Vector, reserve) {
    size_t size = 3;
    int value = 5;
    size_t cap = 9;
    ft::vector<int> target(size, value);
    std::vector<int> stl(size, value);
    
    target.reserve(cap);
    expect_size_value_cap(target, size, value, cap);
    
    expect_eq_stl_to_ft(stl, target);
}



TEST(Vector, assign){
    // size_t size = 3;
    // int value = 5;
    // size_t cap = 5;
    // ft::vector<int> target(size, value);
    // target.reserve(cap);
    
    // // capより大きいケース
    // size_t next_size = 7;
    // int next_value = 10;
    // target.assign(next_size, next_value);
    // expect_size_value_cap(target, next_size, next_value, next_size);
    
    // // sizeより大きいケース
    // size_t next_cap = 10;
    // target.reserve(next_cap);
    // next_size = 8;
    // target.assign(next_size, next_value);
    // expect_size_value_cap(target, next_size, next_value, next_cap);
    
    // // sizeより小さいケース
    // next_size = 3;
    // target.assign(next_size, next_value);
    // expect_size_value_cap(target, next_size, next_value, next_cap);
    
    // 範囲指定 inputstream
    std::stringstream ss;
    std::stringstream ss2;
    ss << 1 << 2 << 3;
    ss2 << 1 << 2 << 3;
    std::istream_iterator<int> it_stl(ss);
    std::istream_iterator<int> it_ft(ss2);
    std::istream_iterator<int> ite;
    
    std::vector<int> stl_2(3, 1);
    ft::vector<int> ft_2(3, 1);
    
    // ちゃんとはいってない
    ft_2.assign(it_ft, ite);
    stl_2.assign(it_stl, ite);
    expect_eq_stl_to_ft(stl_2, ft_2);
    
    // 範囲 forward iter
    size_t size = 10;
    int value = 5;
    std::vector<int> for_iter(size, value);

    std::vector<int>::iterator it_ft_3 = for_iter.begin();
    std::vector<int>::iterator it_stl_3 = for_iter.begin();
    std::vector<int>::iterator it_end = for_iter.end();
  
    // iterがcapより大きい
    ft::vector<int> ft_3(3,3);
    std::vector<int> stl_3(3, 3);
    ft_3.assign(it_ft_3, it_end);
    stl_3.assign(it_stl_3, it_end);
    expect_eq_stl_to_ft(stl_3, ft_3);

    // iterがsizeより小さい
    it_ft_3 = for_iter.begin();
    it_stl_3 = for_iter.begin();
    ft::vector<int> ft_4(20,3);
    std::vector<int> stl_4(20, 3);
    ft_4.assign(it_ft_3, it_end);
    stl_4.assign(it_stl_3, it_end);
    expect_eq_stl_to_ft(stl_4, ft_4);
    // sizeより大きくcapより小さい
    
    it_ft_3 = for_iter.begin();
    it_stl_3 = for_iter.begin();
    ft::vector<int> ft_5(5,3);
    std::vector<int> stl_5(5, 3);
    ft_5.reserve(10);
    stl_5.reserve(10);
    ft_5.assign(it_ft_3, it_end);
    stl_5.assign(it_stl_3, it_end);
    expect_eq_stl_to_ft(stl_5, ft_5);
}

TEST(Vector, popback) {
    size_t size = 3;
    long value = 10;
    std::vector<long> stl(3, 10);
    ft::vector<long> ft(3, 10);
    
    // 引数1つ
    stl.pop_back();
    ft.pop_back();
    expect_eq_stl_to_ft(stl, ft);
}

TEST(Vector, insert) {
    size_t size = 3;
    long value = 10;
    std::vector<long> stl(3, 10);
    ft::vector<long> ft(3, 10);
    
    size_t cap = 7;
    
    stl.reserve(cap);
    ft.reserve(cap);
    // 1.capがある場合
    // 終端に挿入
    stl.insert(stl.end(), 1);
    ft.insert(ft.end(), 1);
    expect_eq_stl_to_ft(stl, ft);
    
    // それ以外
    std::vector<long>::iterator stl_it = stl.begin();
    ft::vector<long>::iterator ft_it = ft.begin();
    stl_it += 2;
    ft_it += 2;

    stl.insert(stl_it, 1);
    ft.insert(ft_it, 1);
    expect_eq_stl_to_ft(stl, ft);
    
    // 2.capがない場合
    stl.resize(3, 3); 
    ft.resize(3, 3);
    stl.insert(stl.end(), 1);
    ft.insert(ft.end(), 1);
    expect_eq_stl_to_ft(stl, ft);
    
    // 3.size指定
    stl.insert(stl.end(), 5, 3);
    ft.insert(ft.end(), 5, 3);
    expect_eq_stl_to_ft(stl, ft);
    
    // 4.範囲指定 inputstream
    std::stringstream ss;
    std::stringstream ss2;
    ss << 1 << 2 << 3;
    ss2 << 1 << 2 << 3;
    std::istream_iterator<int> it_stl(ss);
    std::istream_iterator<int> it_ft(ss2);
    std::istream_iterator<int> ite;
    
    std::vector<int> stl_2(3, 3);
    ft::vector<int> ft_2(3, 3);
    
    stl_2.insert(stl_2.end(), it_stl, ite);
    ft_2.insert(ft_2.end(), it_ft, ite);
    expect_eq_stl_to_ft(stl_2, ft_2);
    
    // forward iter
    // iterがsizeより小さい
    size = 2;
    value = 5;
    std::vector<int> for_iter(size, value);

    std::vector<int>::iterator it_ft_3 = for_iter.begin();
    std::vector<int>::iterator it_stl_3 = for_iter.begin();
    std::vector<int>::iterator it_end = for_iter.end();

    it_ft_3 = for_iter.begin();
    it_stl_3 = for_iter.begin();
    ft::vector<int> ft_4(20,3);
    std::vector<int> stl_4(20, 3);
    ft_4.insert(ft_4.begin(), it_ft_3, it_end);
    stl_4.insert(stl_4.begin(), it_stl_3, it_end);
    expect_eq_stl_to_ft(stl_4, ft_4);
    
    // sizeより大きくcapより小さい
    // elem_afterが大きい
    it_ft_3 = for_iter.begin();
    it_stl_3 = for_iter.begin();
    ft::vector<int> ft_5(5,3);
    std::vector<int> stl_5(5, 3);
    ft_5.reserve(10);
    stl_5.reserve(10);
    ft_5.insert(ft_5.begin(), it_ft_3, it_end);
    stl_5.insert(stl_5.begin(), it_stl_3, it_end);
    expect_eq_stl_to_ft(stl_5, ft_5);
    
    // elem_after < size 
    it_ft_3 = for_iter.begin();
    it_stl_3 = for_iter.begin();
    ft::vector<int> ft_6(5,3);
    std::vector<int> stl_6(5, 3);
    ft_6.reserve(10);
    stl_6.reserve(10);
    ft_6.insert(ft_6.end(), it_ft_3, it_end);
    stl_6.insert(stl_6.end(), it_stl_3, it_end);
    expect_eq_stl_to_ft(stl_6, ft_6);
}

TEST(Vector, erase) {
    size_t size = 3;
    int value = 10;
    std::vector<int> stl(size, value);
    ft::vector<int> ft(size, value);
    
    std::vector<int>::iterator stl_it = stl.erase(--stl.end());
    ft::vector<int>::iterator ft_it = ft.erase(--ft.end());
    expect_eq_stl_to_ft(stl, ft);
    // pos が最後の要素を参照する場合は、 end() イテレータが返されます。
    EXPECT_EQ(stl_it, stl.end());
    EXPECT_EQ(ft_it, ft.end());
    
    stl_it = stl.erase(stl.begin());
    ft_it = ft.erase(ft.begin());
    expect_eq_stl_to_ft(stl, ft);
    EXPECT_EQ(stl_it, stl.begin());
    EXPECT_EQ(ft_it, ft.begin());
    
    size = 5;
    value = 10;
    std::vector<int> stl_2(size, value);
    ft::vector<int> ft_2(size, value);
    
    std::vector<int>::iterator stl_begin = stl_2.begin();
    std::vector<int>::iterator stl_end = stl_2.end();
    ft::vector<int>::iterator ft_begin = ft_2.begin();
    ft::vector<int>::iterator ft_end = ft_2.end();
    stl_begin++;
    ft_begin++;
    stl_end--;
    ft_end--;
    
    stl_it = stl_2.erase(stl_begin, stl_end);
    ft_it = ft_2.erase(ft_begin, ft_end);
    stl_it++;
    ft_it++;
    expect_eq_stl_to_ft(stl, ft);
    EXPECT_EQ(stl_it, stl_2.end());
    EXPECT_EQ(ft_it, ft_2.end());
    
}

TEST(Vector, clear) {
    size_t size = 3;
    int value = 10;
    std::vector<int> stl(size, value);
    ft::vector<int> ft(size, value);
    stl.clear();
    ft.clear();
    
    expect_eq_stl_to_ft(stl, ft);
}

TEST(Vector, swap) {
    ft::vector<std::string> target;
    target.push_back("1");
    target.push_back("2");
    target.push_back("3");
    ft::vector<std::string> swapper;
    target.swap(swapper);
    
    EXPECT_TRUE(target.empty());
    ft::vector<std::string>::iterator itr = swapper.begin();
    EXPECT_EQ(*itr++, "1");
    EXPECT_EQ(*itr++, "2");
    EXPECT_EQ(*itr++, "3");
    EXPECT_TRUE(itr == swapper.end());
}

TEST(Vector, operator) {
    size_t size = 3;
    int value = 10;
    ft::vector<int> ft_1(size, value);
    ft::vector<int> ft_2(size, value);
    
    EXPECT_TRUE(ft_1 == ft_2);
    ft_2.push_back(4);
    EXPECT_TRUE(ft_1 != ft_2);
    EXPECT_TRUE(ft_1 < ft_2);
     
    ft_1.push_back(5);
    EXPECT_TRUE(ft_1 > ft_2);
}

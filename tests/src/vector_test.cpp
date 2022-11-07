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

TEST(Vector, reserve) {
    size_t size = 3;
    int value = 5;
    size_t cap = 9;
    ft::vector<int> target(size, value);
    
    target.reserve(cap);
    expect_size_value_cap(target, size, value, cap);
}

TEST(Vector, assign){
    size_t size = 3;
    int value = 5;
    size_t cap = 5;
    ft::vector<int> target(size, value);
    target.reserve(cap);
    
    // capより大きいケース
    size_t next_size = 7;
    int next_value = 10;
    target.assign(next_size, next_value);
    expect_size_value_cap(target, next_size, next_value, next_size);
    
    // sizeより大きいケース
    size_t next_cap = 10;
    target.reserve(next_cap);
    next_size = 8;
    target.assign(next_size, next_value);
    expect_size_value_cap(target, next_size, next_value, next_cap);
    
    // sizeより小さいケース
    next_size = 3;
    target.assign(next_size, next_value);
    expect_size_value_cap(target, next_size, next_value, next_cap);
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

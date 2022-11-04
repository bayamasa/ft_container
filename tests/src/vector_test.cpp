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
void expect_eq_vector(std::vector<T, Allocator>& stl, ft::vector<T, Allocator>& ft) {
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

TEST(Vector, DefaultConstructor) {
    std::vector<int> stl;
    ft::vector<int> ft;
    expect_eq_vector(stl, ft);
}

TEST(Vector, FillConstructor) {
    size_t size = 10;
    int value = 5;
    std::vector<int> stl(size, value);
    ft::vector<int> ft(size, value);
    
    expect_eq_vector(stl, ft);
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

    expect_eq_vector(stl, ft);
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
    
    debug_print(stl, ft);
    expect_eq_vector(stl, ft);
}

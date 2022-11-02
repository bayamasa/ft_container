#include "vector.hpp"

#include <vector>
#include <gtest/gtest.h>

template <typename T, typename Allocator>
void expect_eq_attrs(std::vector<T, Allocator>& stl, ft::vector<T, Allocator>& ft) {
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
    expect_eq_attrs(stl, ft);
}

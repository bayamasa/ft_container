#include <iterator>
#include <iostream>
#include <vector>
#include <list>

int main()
{
  {
    std::vector<int> v = {3, 1, 4};
    std::size_t d = std::distance(v.begin(), v.end());

    std::cout << d << std::endl;
  }
  {
    std::list<int> ls = {3, 1, 4, 5, 2};
    std::size_t d = std::distance(ls.begin(), ls.end());

    std::cout << d << std::endl;
  }
}

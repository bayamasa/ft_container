#include "vector_exp.hpp"

int main(void)
{
    ft::vector<int> v(10, 1) ;
    v[2] = 99 ;
    v.resize(5) ;
    // vは{1,1,99,1,1}
}

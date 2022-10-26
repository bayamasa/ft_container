#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <stddef.h>
#include "iterator_traits.hpp"

namespace ft {

template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
        typename _Pointer = _Tp*, typename _Reference = _Tp&>
struct iterator
{
    typedef _Category  iterator_category;
    typedef _Tp        value_type;
    typedef _Distance  difference_type;
    typedef _Pointer   pointer;
    typedef _Reference reference;
};



class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, 


}


#endif

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <stddef.h>
#include "iterator_traits.hpp"

namespace ft {

// template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
//         typename _Pointer = _Tp*, typename _Reference = _Tp&>
// struct iterator
// {
//     typedef _Category  iterator_category;
//     typedef _Tp        value_type;
//     typedef _Distance  difference_type;
//     typedef _Pointer   pointer;
//     typedef _Reference reference;
// };


template <class Iter>
class wrap_iterator
{
public: 
    typedef Iter iterator_type;
    typedef typename iterator_traits<iterator_type>::value_type value_type;
    typedef typename iterator_traits<iterator_type>::difference_type difference_type;
    typedef typename iterator_traits<iterator_type>::pointer pointer;
    typedef typename iterator_traits<iterator_type>::reference reference;
    typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
private:
    iterator_type _i;
public:
    wrap_iterator() : _i() {};
    wrap_iterator(iterator_type _x) : _i(_x) {};
    wrap_iterator(const wrap_iterator& __x) : _i(__x._i) {};
    template<class Iter>
    wrap_iterator(const wrap_iterator<Iter>& __x) : _i(__x._i) {};
    
    template<typename Iter>
    wrap_iterator& operator=(const wrap_iterator<Iter>& __x) {
        _i = __x._i;
        return *this;
    }
    
    reference operator*() const {
        return *_i;
    }

    pointer operator->() const {
        return &(*_i);
    }

    wrap_iterator& operator++() {
        ++_i;
        return *this;
    }
    
    wrap_iterator operator++(int) {
        wrap_iterator _tmp(*this);
        ++(*this);
        return __tmp;
    }
    
    wrap_iterator& operator--() {
        --_i;
        return *this;
    }
    
    wrap_iterator operator+ (difference_type _n) const {
        wrap_iterator _w(*this);
        _w += _n;
        return _w;
    }
    
    wrap_iterator& operator+=(difference_type _n) {
        _i += _n;
        return *this;
    }
    
    wrap_iterator operator-(difference_type _n) const {
        return *this + (-_n);
    }
    
    wrap_iterator& operator-=(difference_type _n) {
        *this += -_n;
        return *this;
    } 
    
    reference operator[](difference_type _n) const {
        return _i[_n];
    }
    
    iterator_type base() const {
        return _i;
    }
};

    template <class Iter1>
    bool operator==(const wrap_iterator<Iter1>& _x, const wrap_iterator<Iter1>& _y) {
        return _x.base() == _y.base();
    }
    template <class Iter1, class Iter2>
    bool operator==(const wrap_iterator<Iter1>& _x, const wrap_iterator<Iter2>& _y) {
        return _x.base() == _y.base();
    }
    template <class Iter1>
    bool operator<(const wrap_iterator<Iter1>& _x, const wrap_iterator<Iter1>& _y) {
        return _x.base() < _y.base();
    }
    template <class Iter1, class Iter2>
    bool operator<(const wrap_iterator<Iter1>& _x, const wrap_iterator<Iter2>& _y) {
        return _x.base() < _y.base();
    }
    
    template <class Iter1>
    bool operator!=(const wrap_iterator<Iter1>& _x, const wrap_iterator<Iter1>& _y) {
        return !(_x == _y);
    }
    
    template <class Iter1, class Iter2>
    bool operator!=(const wrap_iterator<Iter1>& _x, const wrap_iterator<Iter2>& _y) {
        return !(_x == _y);
    }

    template <class Iter1>
    bool operator>(const wrap_iterator<Iter1>& _x, const wrap_iterator<Iter1>& _y) {
        return _y < _x;
    }
    
    template <class Iter1, class Iter2>
    bool operator>(const wrap_iterator<Iter1>& _x, const wrap_iterator<Iter2>& _y) {
        return _y < _x;
    }
    
    template <class Iter1>
    bool operator>=(const wrap_iterator<Iter1>& _x, const wrap_iterator<Iter1>& _y) {
        return !(__x < __y);
    }
    
    template <class Iter1, class Iter2>
    bool operator>=(const wrap_iterator<Iter1>& _x, const wrap_iterator<Iter2>& _y) {
        return !(__x < __y);
    }
    
    template <class Iter1>
    bool operator<=(const wrap_iterator<Iter1>& _x, const wrap_iterator<Iter1>& _y) {
        return !(_y < _x);
    }
    
    template <class Iter1, class Iter2>
    bool operator<=(const wrap_iterator<Iter1>& _x, const wrap_iterator<Iter2>& _y) {
        return !(_y < _x);
    }
    
    template <class Iter1, class Iter2>
    typename wrap_iterator<Iter1>::difference_type
    operator-(const wrap_iterator<Iter1>& __x, const wrap_iterator<Iter2>& __y) 
    {
        return __x.base() - __y.base();
    }
    
    template<class Iter1>
    wrap_iterator<Iter1> operator+(typename wrap_iterator<Iter1>::difference_type _n,  wrap_iterator<Iter1> _x)
    {
        _x += _n;
        return _x;
    }
}

#endif

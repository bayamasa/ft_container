#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {

template <class Iter>
class reverse_iterator
{
public: 
    typedef Iter iterator_type;
    typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
    typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
    typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
    typedef typename ft::iterator_traits<iterator_type>::reference reference;
    typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;
private:
    iterator_type _i;
public:
    reverse_iterator() : _i() {};
    reverse_iterator(iterator_type _x) : _i(_x) {};
    reverse_iterator(const reverse_iterator& __x) : _i(__x._i) {};

    template<class _Up>
    reverse_iterator(const reverse_iterator<_Up>& __x) : _i(__x._i) {};
    
    template<typename _Up>
    reverse_iterator& operator=(const reverse_iterator<_Up>& __x) {
        _i = __x._i;
        return *this;
    }
    
    reference operator*() const {
        Iter __tmp = _i;
        return *--__tmp;
    }

    pointer operator->() const {
        Iter __tmp = _i;
	    --__tmp;
        return &(*__tmp);
    }

    reverse_iterator& operator++() {
        --_i;
        return *this;
    }
    
    reverse_iterator operator++(int) {
        reverse_iterator _tmp(*this);
        --(*this);
        return _tmp;
    }
    
    reverse_iterator& operator--() {
        ++_i;
        return *this;
    }
    
    reverse_iterator operator--(int) {
        reverse_iterator __tmp = *this;
        ++_i;
        return __tmp;
    }
    
    reverse_iterator operator+ (difference_type _n) const {
        return reverse_iterator(_i - _n);
    }
    
    reverse_iterator& operator+=(difference_type _n) {
        _i -= _n;
        return *this;
    }
    
    reverse_iterator operator-(difference_type _n) const {
        return reverse_iterator(_i + _n);
    }
    
    reverse_iterator& operator-=(difference_type _n) {
        _i += _n;
        return *this;
    } 
    
    reference operator[](difference_type _n) const {
        return *(*this + _n);
    }
    
    iterator_type base() const {
        return _i;
    }
};

    template <class Iter1>
    bool operator==(const reverse_iterator<Iter1>& _x, const reverse_iterator<Iter1>& _y) {
        return _x.base() == _y.base();
    }
    template <class Iter1, class Iter2>
    bool operator==(const reverse_iterator<Iter1>& _x, const reverse_iterator<Iter2>& _y) {
        return _x.base() == _y.base();
    }
    template <class Iter1>
    bool operator<(const reverse_iterator<Iter1>& _x, const reverse_iterator<Iter1>& _y) {
        return _y.base() < _x.base();
    }
    template <class Iter1, class Iter2>
    bool operator<(const reverse_iterator<Iter1>& _x, const reverse_iterator<Iter2>& _y) {
        return _y.base() < _x.base();
    }
    
    template <class Iter1>
    bool operator!=(const reverse_iterator<Iter1>& _x, const reverse_iterator<Iter1>& _y) {
        return !(_x == _y);
    }
    
    template <class Iter1, class Iter2>
    bool operator!=(const reverse_iterator<Iter1>& _x, const reverse_iterator<Iter2>& _y) {
        return !(_x == _y);
    }

    template <class Iter1>
    bool operator>(const reverse_iterator<Iter1>& _x, const reverse_iterator<Iter1>& _y) {
        return _x < _y;
    }
    
    template <class Iter1, class Iter2>
    bool operator>(const reverse_iterator<Iter1>& _x, const reverse_iterator<Iter2>& _y) {
        return _x < _y;
    }
    
    template <class Iter1>
    bool operator>=(const reverse_iterator<Iter1>& _x, const reverse_iterator<Iter1>& _y) {
        return !(_y < _x);
    }
    
    template <class Iter1, class Iter2>
    bool operator>=(const reverse_iterator<Iter1>& _x, const reverse_iterator<Iter2>& _y) {
        return !(_y < _x);
    }
    
    template <class Iter1>
    bool operator<=(const reverse_iterator<Iter1>& _x, const reverse_iterator<Iter1>& _y) {
        return !(_x < _y);
    }
    
    template <class Iter1, class Iter2>
    bool operator<=(const reverse_iterator<Iter1>& _x, const reverse_iterator<Iter2>& _y) {
        return !(_x < _y);
    }
    
    template <class Iter1, class Iter2>
    typename reverse_iterator<Iter1>::difference_type
    operator-(const reverse_iterator<Iter1>& __x, const reverse_iterator<Iter2>& __y) 
    {
        return __y.base() - __x.base();
    }
    
    template<class Iter1>
    reverse_iterator<Iter1> operator+(typename reverse_iterator<Iter1>::difference_type _n,  reverse_iterator<Iter1> _x)
    {
        reverse_iterator<Iter1>(_x.base() - _n);
    }
}

#endif

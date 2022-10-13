#include <cstddef>
#include <iterator>
#include <iostream>
#include <algorithm>

template <typename Array>
struct array_iterator
{
    Array &a;
    // 現在の指し示しているindex
    std::size_t i;
    array_iterator(Array &a, std::size_t i) : a(a), i(i) {};
    array_iterator operator ++()
    {
        ++i;
        return *this;
    };
    
    array_iterator operator ++(int)
    {
        array_iterator copy = *this;
        ++*this;
        return copy;
    };

    array_iterator operator --()
    {
        --i;
        return *this;
    };
    
    array_iterator operator --(int) {
        array_iterator copy = *this;
        --*this;
        return copy;
    }
    
    array_iterator operator += (std::size_t n) {
        i += n;
        return *this;
    }
    array_iterator operator + (std::size_t n) const {
        array_iterator copy = *this;
        copy += n;
        return copy;
    }
    
    array_iterator operator -= (std::size_t n) {
        i -= n;
        return *this;
    }
    array_iterator operator - (std::size_t n) const {
        array_iterator copy = *this;
        copy -= n;
        return copy;
    }

    typename Array::reference operator *(){
        return a[i];
    };
    
    typename Array::reference operator [](std::size_t n) const {
        return *(*this + n);
    }
    
    bool operator ==(array_iterator const & right) {
        return i == right.i;
    }
    bool operator !=(array_iterator const & right) {
        return i != right.i;
    }
     
};


template <typename T, std::size_t N>
struct array
{
    // using value_type = T;
    typedef T & reference;
    // using const_reference = T const &;
    typedef array_iterator<array> iterator;
    
    // using size_type = std::size_t;
    T storage[N];
    
    T & operator[] (std::size_t i) {
        return storage[i];
    }
    
    const T & operator[] (std::size_t i) const {
        return storage[i];
    }
    
    iterator begin(){
        // *thisはメンバ関数を呼んだオブジェクトの参照
        return iterator(*this, 0);
    };
    iterator end() {
        return iterator(*this, N);
    };
};

int main(void)
{
    array<int, 5> a = {1, 2, 3, 4, 5};
    for (array<int, 5>::iterator i = std::begin(a); i != std::end(a); i++) {
        std::cout << *i << std::endl;
    }
    array<int, 5>::iterator i = std::begin(a);
    std::cout << i[3];
}

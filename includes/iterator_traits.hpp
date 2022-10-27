#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

namespace ft {
    
    // https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/bits/stl_iterator_base_types.h
    struct input_iterator_tag { };

    ///  Marking output iterators.
    struct output_iterator_tag { };

    /// Forward iterators support a superset of input iterator operations.
    struct forward_iterator_tag : public input_iterator_tag { };

    /// Bidirectional iterators support a superset of forward iterator
    /// operations.
    struct bidirectional_iterator_tag : public forward_iterator_tag { };

    /// Random-access iterators support a superset of bidirectional
    /// iterator operations.
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };
    
    template <typename Iterator> 
    struct iterator_traits {
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };
    
    template <typename T>
    struct iterator_traits<T *> {
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef ft::random_access_iterator_tag iterator_category;
    };
    
    template <class T>
    struct iterator_traits<const T*> {
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef ft::random_access_iterator_tag iterator_category;
    };
}

#endif


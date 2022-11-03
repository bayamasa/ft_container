#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <stdexcept>
#include <memory>
#include "type_traits.hpp"
#include "iterator.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include <deque>
#include <limits>

namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
class vector
{
    public: 
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef value_type &                    reference;
        typedef const value_type &              const_reference;
        
        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;
    
        typedef ft::wrap_iterator<pointer>          iterator;
        typedef ft::wrap_iterator<const_pointer>    const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        
        explicit vector(const Allocator& a = Allocator()) 
        :  __start_(NULL), __finish_(NULL), __end_of_storage_(NULL), __alloc_(a){};
        
        explicit vector(size_type __n, const_reference __value = T(),
                const Allocator& __a = Allocator())
        : __start_(NULL), __finish_(NULL), __end_of_storage_(NULL), __alloc_(__a)
        {
            __vallocate(__n);            
            __finish_ = __uninitialized_fill_n(__start_, __n, __value);
        }
        template <class _InputIter>
        vector(_InputIter __first, _InputIter __last,
                const Allocator& __a = Allocator(),
                typename ft::enable_if<!ft::is_integral<_InputIter>::value>::type* = NULL) 
        : __start_(NULL), __finish_(NULL), __end_of_storage_(NULL),__alloc_(__a)
        {
            __range_initialize(__first, __last, iterator_traits<_InputIter>::iterator_category);
        };
        
        vector(const vector & x);
        ~vector(){};
        vector & operator =(const vector & x);
        
        iterator begin() { return __start_; }
        const_iterator begin() const { return __start_; }
        iterator end() { return __finish_; }
        const_iterator end() const { return __finish_; }
        
        reverse_iterator rbegin() { return reverse_iterator(__finish_); }
        const_reverse_iterator rbegin() const { return reverse_iterator(__finish_); }
        reverse_iterator rend() { return reverse_iterator(__start_); }
        const_reverse_iterator rend() const { return reverse_iterator(__start_); }
        
        size_type size() const {
            return size_type(__finish_ - __start_);
        }
        size_type max_size() const{
            return std::min<size_type>(__alloc_.max_size(),
                                 std::numeric_limits<difference_type>::max());
        }
                    
        void resize(size_type sz, value_type c = value_type()) {
            if (sz < size()) {
                size_type diff = size() - sz;
                destroy_until(rbegin() + diff);
                __finish_ = __start_ + sz;
            } else if ( sz > size()) {
                reserve(sz);
                for (; __finish_ != __end_of_storage_; ++__finish_) {
                    construct(__finish_, c);
                }
            }
        }
        
        size_type capacity() const {
            return size_type(__end_of_storage_ - __start_);
        }
        
        bool empty() const {
            return size() == 0;
        }
        
        void reserve(size_type __n) {
            if (__n > max_size())
                throw std::length_error("vector::reserve");
            if (capacity() < __n) {
                const size_type __old_size = size();
                pointer __tmp = __allocate_and_copy(__n, __start_, __finish_);
                __deallocate(__start_, __end_of_storage_ - __start_);
                __start_ = __tmp;
                __finish_ = __tmp + __old_size;
                __end_of_storage_ = __start_ + __n;
            }
        }
        
        reference operator [](size_type i) {
            return __start_[i];
        }
        const_reference operator [](size_type i) const {
            return __start_[i];
        }
        
        reference at(size_type i) {
            if (i >= size())
                throw std::out_of_range("index is out of range.");
            return __start_[i];
        }
        
        const_reference at(size_type i) const {
            if (i >= size())
                throw std::out_of_range("index is out of range.");
            return __start_[i];
        }
        
        pointer data()
        { return __start_; }

        const_pointer data() const
        { return __start_; }
        
        reference front()
        { return __start_; }

        const_reference front() const
        { return __start_; }

        reference back()
        { return __finish_ - 1; }

        const_reference back() const
        { return __finish_ - 1; }
        
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last); 
        
        void assign(size_type n, const T& u);
        
        
        void push_back(const_reference value) {
            // 予約メモリーが足りなければ拡張
            if (size() + 1 > capacity()) {
                __realloc_insert(end(), value);
            }
            else
            {
                construct(__finish_, value);
                ++__finish_;
            }
            
        }
        
        void pop_back();
        
        iterator insert(iterator position, const T& x);
        
        void insert(iterator position,
            size_type n, const T& x);    
        
        template <class InputIterator>
        void insert(iterator position,
            InputIterator first,
            InputIterator last);

        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);
        
        void swap(vector& x);
        
        void clear() {
            destroy_until(rend());
        }
        
        allocator_type get_allocator() const;
        
        void construct(pointer ptr) {
            __alloc_traits::construct(__alloc_, ptr);
        }
        void construct(pointer ptr, const_reference value) {
            __alloc_traits::construct(__alloc_, ptr, value);
        }
        
    private: 
        pointer __start_;
        pointer __finish_;
        pointer __end_of_storage_;
        allocator_type __alloc_;
        
        typedef std::allocator_traits<allocator_type> __alloc_traits;
        
        template <class _ForwardIterator, class _Size, class _T>
        _ForwardIterator
        __uninitialized_fill_n(_ForwardIterator __first, _Size __n, const _T & __x)
        {
            _ForwardIterator __cur = __first;
            try {
                for (; __n > 0; --__n, (void) ++__cur) {
                    __alloc_.construct(__cur, __x);
                }
                return __cur;
            } catch(...) {
                for (; __cur != __first; (void) ++__first) 
                    __alloc_.destroy(__first);
                throw;
            }
        }
        template<typename _ForwardIterator>
        pointer __allocate_and_copy(size_type __n,
                        _ForwardIterator __first, _ForwardIterator __last)
        {
            pointer __result = __alloc_.allocate(__n);
            try
            {
                __uninitialized_copy(__first, __last, __result);
                return __result;
            }
            catch(...)
            {
                __deallocate(__first, __n);
                throw;
            }
        }
        
        template<typename _InputIterator, typename _ForwardIterator>
        _ForwardIterator __uninitialized_copy(_InputIterator __first, _InputIterator __last, 
                _ForwardIterator __result)
        {
            _ForwardIterator __cur = __result;
            try {
                for (; __first != __last; ++__first, (void)++__cur) {
                    __alloc_.construct(__cur, *__first);
                }
                return __cur;
            } catch(...) {
                for (; __cur != __result; (void)++__result) 
                    __alloc_.destroy(__result);
                throw;
            }
        }
        
        
        template<typename _InputIterator>
        void __range_initialize(_InputIterator __first, _InputIterator __last, 
                            std::input_iterator_tag)
        {
            try {
                for (; __first != __last; ++__first)
                    push_back(*__first);
            } catch(...) {
                clear();
                throw;
            }
        }
        
        template<typename _ForwardIterator>
        void __range_initialize(_ForwardIterator __first, _ForwardIterator __last, 
                            std::forward_iterator_tag)
        {
            const size_type __n = std::distance(__first, __last);
            if (__n > max_size())
                throw std::length_error("cannot create ft::vector larger than max_size()");
            __start_ = __alloc_.allocate(__n);
            __end_of_storage_ = __start_ + __n;
            __finish_ = __uninitialized_copy(__first, __last, __start_);
        }
        
        void __vallocate(size_type __n) {
            if (__n > max_size())
                throw std::length_error("cannot create ft::vector larger than max_size()");
            __start_ = __alloc_.allocate(__n);
            __finish_ = __start_;
            __end_of_storage_ = __start_ + __n;
        }
        
        void __deallocate(pointer __first, size_type __n) {
            __alloc_.deallocate(__first, __n);
        }

        void destroy(pointer ptr) {
            __alloc_traits::destroy(__alloc_, ptr);
        }
        void destroy_until(reverse_iterator rend) {
            for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --__finish_) {
                destroy(&*riter);
            }
        }
        void __realloc_insert(iterator __position, const_reference __x) {
            const size_type __len = 
                __check_len(size_type(1), "vector::realloc_insert");
            pointer __old_start = __start_;
            pointer __old_finish = __finish_;
            const size_type __elems_before = __position - begin();
            // 箱のメモリ確保
            pointer __new_start = __alloc_.allocate(__len);
            pointer __new_finish = __new_start;
            try
            {
                // 要素のメモリ確保
                __alloc_.construct(__new_start + __elems_before, __x);
                __new_finish = __uninitialized_copy(__old_start, __position.base(), __new_start);
                ++__new_finish;
                __new_finish = __uninitialized_copy(__position.base(), __old_finish, __new_finish);
            }
            catch(...)
            {
                if (!__new_finish)
                    __alloc_.destroy(__new_start + __elems_before);
                else 
                    __alloc_.destroy(__new_start + __new_finish);
                __deallocate(__new_start, __len);
                throw;
            }
            
            
        }
        
        size_type __check_len(size_type __n, const char *__s) const {
            if (max_size() - size() < __n)
                throw std::length_error(__s);
            // sizeの2倍取る
            const size_type __len = size() + (std::max)(size(), __n);
            // オーバーフローしてたら、max_size適用
            return (__len < size() || __len > max_size()) ? max_size() : __len;
        }
        
};

}

#endif

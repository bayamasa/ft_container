#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <stdexcept>
#include <memory>
#include "type_traits.hpp"
#include "iterator.hpp"
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
        
        explicit vector(const Allocator& a = Allocator()) : __alloc_(a){};
        
        explicit vector(size_type __n, const_reference __value = T(),
                const Allocator& __a = Allocator()) : __alloc_(__a)
        {
            __vallocate(__n);            
            __last_ = __uninitialized_fill_n(__first_, __n, __value);
        }
        template <class InputIter>
        vector(InputIter first, InputIter last,
                const Allocator& a = Allocator(),
                typename ft::enable_if<!ft::is_integral<InputIter>::value>::type* = NULL) : __alloc_(a)
        {
            reserve(std::distance(first, last));
            for (InputIter i = first; i != last ; ++i)
            {
                push_back(*i);
            }
        };
        
        vector(const vector & x);
        ~vector(){};
        vector & operator =(const vector & x);
        
        iterator begin() { return __first_; }
        const_iterator begin() const { return __first_; }
        iterator end() { return __last_; }
        const_iterator end() const { return __last_; }
        
        reverse_iterator rbegin() { return reverse_iterator(__last_); }
        const_reverse_iterator rbegin() const { return reverse_iterator(__last_); }
        reverse_iterator rend() { return reverse_iterator(__first_); }
        const_reverse_iterator rend() const { return reverse_iterator(__first_); }
        
        size_type size() const {
            return end() - begin();
        }
        size_type max_size() const{
            return std::min<size_type>(__alloc_.max_size(),
                                 std::numeric_limits<difference_type>::max());
        }
                    
        void resize(size_type sz, value_type c = value_type()) {
            if (sz < size()) {
                size_type diff = size() - sz;
                destroy_until(rbegin() + diff);
                __last_ = __first_ + sz;
            } else if ( sz > size()) {
                reserve(sz);
                for (; __last_ != __end_of_storage_; ++__last_) {
                    construct(__last_, c);
                }
            }
        }
        
        size_type capacity() const {
            return __end_of_storage_ - __first_;
        }
        
        bool empty() const {
            return size() == 0;
        }
        
        void reserve(size_type sz) {
            if (sz <= capacity())
                return ;
            // 動的メモリの確保
            pointer ptr = NULL;
            __vallocate(sz);
            
            // 古いストレージ情報を保存
            pointer old_first = __first_;
            pointer old_last = __last_;
            size_type old_capacity = capacity(); 
            
            // 新しいストレージに差し替え
            __first_ = ptr;
            __last_ = __first_;
            __end_of_storage_ = __first_ + sz;
            
            // 古いストレージから新しいストレージに要素を差し替え
            for (pointer old_iter = old_first; old_iter != old_last; ++old_iter, ++__last_) {
                construct(__last_, std::move(*old_iter));
            }
            for (reverse_iterator riter = reverse_iterator(old_last), rend = reverse_iterator(old_first);
                    riter != rend; ++riter) {
                destroy(&*riter);            
            }
              // 古いストレージの破棄
            __alloc_traits::deallocate(__alloc_, old_first, old_capacity);
        }
        
        reference operator [](size_type i) {
            return __first_[i];
        }
        const_reference operator [](size_type i) const {
            return __first_[i];
        }
        
        reference at(size_type i) {
            if (i >= size())
                throw std::out_of_range("index is out of range.");
            return __first_[i];
        }
        
        const_reference at(size_type i) const {
            if (i >= size())
                throw std::out_of_range("index is out of range.");
            return __first_[i];
        }
        
        pointer data()
        { return __first_; }

        const_pointer data() const
        { return __first_; }
        
        reference front()
        { return __first_; }

        const_reference front() const
        { return __first_; }

        reference back()
        { return __last_ - 1; }

        const_reference back() const
        { return __last_ - 1; }
        
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last); 
        
        void assign(size_type n, const T& u);
        
        
        void push_back(const_reference value) {
            // 予約メモリーが足りなければ拡張
            if (size() + 1 > capacity()) {
                // 現在のストレージサイズ
                size_type c = size();
                // 0の場合は1に
                if ( c == 0 )
                    c = 1 ;
                else
                    // それ以外の場合は2倍する
                    c *= 2 ;
                reserve( c ) ;
            }
            
            construct(__last_, value);
            ++__last_;
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
        pointer __first_;
        pointer __last_;
        pointer __end_of_storage_;
        allocator_type __alloc_;
        
        typedef std::allocator_traits<allocator_type> __alloc_traits;
        
        // Called by constructors to check initial size.
        size_type __check_init_len(size_type __n, const allocator_type & __a) {
            if (__n > max_size(__a))
                throw std::length_error("cannot create ft::vector larger than max_size()");
            return __n;
        }
        

        
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
        
        void __vallocate(size_type __n) {
            if (__n > max_size())
                throw std::length_error("cannot create ft::vector larger than max_size()");
            __first_ = __alloc_.allocate(__n);
            __last_ = __first_;
            __end_of_storage_ = __first_ + __n;
        }
        void deallocate() {
            __alloc_traits::deallocate(__alloc_, __first_, capacity());
        };

        void destroy(pointer ptr) {
            __alloc_traits::destroy(__alloc_, ptr);
        }
        void destroy_until(reverse_iterator rend) {
            for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --__last_) {
                destroy(&*riter);
            }
        }
        
        
};

}

#endif

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <exception>
#include <memory>
#include "type_traits.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"

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
        
        explicit vector(const Allocator& a = Allocator()) : alloc(a){};
        
        explicit vector(size_type n, const T& value = T(),
                const Allocator& a = Allocator()) : alloc(a)
        {
            resize(n, value);
        }
        template <class InputIter>
        vector(InputIter first, InputIter last,
                const Allocator& a = Allocator(),
                typename ft::enable_if<!ft::is_integral<InputIter>::value>::type* = NULL) : alloc(a)
        {
            reserve(std::distance(first, last));
            for (InputIter i = first; i != last ; ++i)
            {
                push_back(*i);
            }
        };
        
        vector (const vector & x);
        ~vector(){};
        vector & operator =(const vector & x);
        
        iterator begin() { return first; }
        const_iterator begin() const { return first; }
        iterator end() { return last; }
        const_iterator end() const { return last; }
        
        reverse_iterator rbegin() { return reverse_iterator(last); }
        const_reverse_iterator rbegin() const { return reverse_iterator(last); }
        reverse_iterator rend() { return reverse_iterator(first); }
        const_reverse_iterator rend() const { return reverse_iterator(first); }
        
        size_type size() const {
            return end() - begin();
        }
        size_type max_size() const;
                    
        void resize(size_type sz, value_type c = value_type()) {
            if (sz < size()) {
                size_type diff = size() - sz;
                destroy_until(rbegin() + diff);
                last = first + sz;
            } else if ( sz > size()) {
                reserve(sz);
                for (; last != reserved_last; ++last) {
                    construct(last, c);
                }
            }
        }
        
        size_type capacity() const {
            return reserved_last - first;
        }
        
        bool empty() const {
            return size() == 0;
        }
        
        void reserve(size_type sz) {
            if (sz <= capacity())
                return ;
            // 動的メモリの確保
            pointer ptr = allocate(sz);
            
            // 古いストレージ情報を保存
            pointer old_first = first;
            pointer old_last = last;
            size_type old_capacity = capacity(); 
            
            // 新しいストレージに差し替え
            first = ptr;
            last = first;
            reserved_last = first + sz;
            
            // 古いストレージから新しいストレージに要素を差し替え
            for (pointer old_iter = old_first; old_iter != old_last; ++old_iter, ++last) {
                construct(last, std::move(*old_iter));
            }
            for (reverse_iterator riter = reverse_iterator(old_last), rend = reverse_iterator(old_first);
                    riter != rend; ++riter) {
                destroy(&*riter);            
            }
              // 古いストレージの破棄
            traits::deallocate(alloc, old_first, old_capacity);
        }
        
        reference operator [](size_type i) {
            return first[i];
        }
        const_reference operator [](size_type i) const {
            return first[i];
        }
        
        reference at(size_type i) {
            if (i >= size())
                throw std::out_of_range("index is out of range.");
            return first[i];
        }
        
        const_reference at(size_type i) const {
            if (i >= size())
                throw std::out_of_range("index is out of range.");
            return first[i];
        }
        
        pointer data()
        { return first; }

        const_pointer data() const
        { return first; }
        
        reference front()
        { return first; }

        const_reference front() const
        { return first; }

        reference back()
        { return last - 1; }

        const_reference back() const
        { return last - 1; }
        
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
            
            construct(last, value);
            ++last;
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
            traits::construct(alloc, ptr);
        }
        void construct(pointer ptr, const_reference value) {
            traits::construct(alloc, ptr, value);
        }
        void construct(pointer ptr, value_type & value) {
            traits::construct(alloc, ptr, std::move(value));
        }
        
    private: 
        // 先頭の要素へのポインター
        pointer first;
        // 最後の要素の1つ前方のポインター
        pointer last;
        // 確保したストレージの終端
        pointer reserved_last;
        // アロケーターの値
        allocator_type alloc;
        
        typedef std::allocator_traits<allocator_type> traits;
        
        pointer allocate(size_type n) {
            return traits::allocate(alloc, n);
        }
        void deallocate() {
            traits::deallocate(alloc, first, capacity());
        };

        void destroy(pointer ptr) {
            traits::destroy(alloc, ptr);
        }
        void destroy_until(reverse_iterator rend) {
            for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --last) {
                destroy(&*riter);
            }
        }
        
        
};

}

#endif

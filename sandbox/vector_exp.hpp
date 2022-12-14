#include <memory>
#include <exception>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <iostream>
#include <vector>
#include <list>
#include "type_trails.hpp"
#include <iterator>

namespace ft
{
    template <typename T, typename Allocator = std::allocator<T> >
class vector
{
    public: 
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef value_type &                    reference;
        typedef const value_type &              const_reference;
        
        typedef allocator_type::size_type       size_type;
        typedef allocator_type::difference_type difference_type;
        typedef allocator_type::pointer         pointer;
        typedef allocator_type::const_pointer   const_pointer;
    
        typedef wrap_iterator<pointer>          iterator;
        typedef wrap_iterator<const_pointer>    const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
               
        vector(size_type n = 0, allocator_type a = allocator_type()) {};
        vector(const allocator_type & alloc) : alloc(alloc) {};
        vector() : vector( allocator_type()) {};
        vector(size_type size, const allocator_type & alloc = allocator_type()){
            resize(size);
        };
        vector(size_type size, const_reference value, const allocator_type & alloc = allocator_type()){
            resize(size, value);
        };
            
        
        ~vector(){};
        vector (const vector & x);
        vector & operator =(const vector & x);
        
        iterator begin() { return first; }
        const_iterator cbegin() const { return first; }
        iterator end() { return last; }
        const_iterator cend() const { return last; }
        
        reverse_iterator rbegin() { return reverse_iterator(last); }
        reverse_iterator rend() { return reverse_iterator(first); }
        
        template < typename InputIterator >
        vector(InputIterator first, InputIterator last, const Allocator & = Allocator(),
        typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
        {
            reserve(std::distance(first, last));
            for (InputIterator i = first; i != last ; ++i)
            {
                push_back(*i);
            }
        }
        
        size_type size() const {
            return cend() - cbegin();
        }
        
        bool empty() const {
            return size() == 0;
        }
        
        size_type capacity() const {
            return reserved_last - first;
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
        reference front()
        { return first; }

        const_reference front() const
        { return first; }

        reference back()
        { return last - 1; }

        const_reference back() const
        { return last - 1; }
        
        pointer data()
        { return first; }

        const_pointer data() const
        { return first; }
        
        void clear() {
            destroy_until(rend());
        }
        
        void construct(pointer ptr) {
            traits::construct(alloc, ptr);
        }
        void construct(pointer ptr, const_reference value) {
            traits::construct(alloc, ptr, value);
        }
        void construct(pointer ptr, value_type && value) {
            traits::construct(alloc, ptr, std::move(value));
        }
        
        void reserve(size_type sz) {
            if (sz <= capacity())
                return ;
            // ????????????????????????
            pointer ptr = allocate(sz);
            
            // ????????????????????????????????????
            pointer old_first = first;
            pointer old_last = last;
            size_type old_capacity = capacity(); 
            
            // ???????????????????????????????????????
            first = ptr;
            last = first;
            reserved_last = first + sz;
            
            // ???????????????????????????????????????????????????????????????????????????
            for (pointer old_iter = old_first; old_iter != old_last; ++old_iter, ++last) {
                construct(last, std::move(*old_iter));
            }
            for (reverse_iterator riter = reverse_iterator(old_last), rend = reverse_iterator(old_first);
                    riter != rend; ++riter) {
                destroy(&*riter);            
            }
              // ??????????????????????????????
            traits::deallocate(alloc, old_first, old_capacity);
        }
            
        void resize(size_type sz) {
            if (sz < size()) {
                size_type diff = size() - sz;
                destroy_until(rbegin() + diff);
                last = first + sz;
            } else if ( sz > size()) {
                reserve(sz);
                for (; last != reserved_last; ++last) {
                    construct(last);
                }
            }
        }
        
        void resize(size_type sz, const_reference value) {
            if (sz < size()) {
                size_type diff = size() - sz;
                destroy_until(rbegin() + diff);
                last = first + sz;
            } else if ( sz > size()) {
                reserve(sz);
                for (; last != reserved_last; ++last) {
                    construct(last, value);
                }
            }
        }
        
        void push_back(const_reference value) {
            // ?????????????????????????????????????????????
            if (size() + 1 > capacity()) {
                // ?????????????????????????????????
                size_type c = size();
                // 0????????????1???
                if ( c == 0 )
                    c = 1 ;
                else
                    // ????????????????????????2?????????
                    c *= 2 ;

                reserve( c ) ;
            }
            
            construct(last, value);
            ++last;
        }
        
        void shrink_to_fit() {
            if (size() == capacity())
                return;
            pointer ptr = allocate(size());
            size_type current_size = size();
            
            for (pointer raw_ptr = ptr, iter = begin(), iter_end = end();
                iter != iter_end; ++iter, ++raw_ptr) {
                    construct(raw_ptr, *iter);
                }
            clear();
            deallocate();
            first = ptr;
            last = ptr + current_size;
            reserved_last = last;
        }
             
    private: 
        // ????????????????????????????????????
        pointer first;
        // ??????????????????1???????????????????????????
        pointer last;
        // ????????????????????????????????????
        pointer reserved_last;
        // ????????????????????????
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


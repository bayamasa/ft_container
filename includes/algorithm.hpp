#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

template <class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
    for (; first1 != last1; ++first1, (void)++first2)
        if (!(*first1 == *first2))
	        return false;
    return true;
}

template< class InputIt1, class InputIt2, class BinaryPredicate >
bool equal( InputIt1 first1, InputIt1 last1,
            InputIt2 first2, BinaryPredicate binary_pred)
{
    for (; first1 != last1; ++first1, (void)++first2)
        if (!bool(binary_pred(*first1, *first2)))
            return false;
    return true;
}

template< class InputIt1, class InputIt2 >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2 )
{
   return lexicographical_compare(first1, last1, first2, last2, __iter_less_tier());
}
                            
template< class InputIt1, class InputIt2, class Compare >
bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2,
                              Compare comp )
{
    for (; first1 != last1 && first2 != last2; first1++, (void)first2++)
    {
        if (comp(first1, first2)) return true;
        if (comp(first2, first1)) return false;
    }
    return first1 == last1 && first2 != last2;
}

template <typename _Iterator1, typename _Iterator2>
bool __iter_less_tier(_Iterator1 __it1, _Iterator2 __it2) {
    return *__it1 < *__it2;
}

#endif

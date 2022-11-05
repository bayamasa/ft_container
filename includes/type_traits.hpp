#ifndef TYPE_TRAILS_HPP
# define TYPE_TRAILS_HPP

namespace ft {

template<typename tType, tType v>
struct __integral_constant
{
    static const tType value = v;
    typedef tType value_type;
    typedef __integral_constant<tType, v> type;
    const value_type operator()() const {
        return value;
    }
};

typedef __integral_constant<bool, true> __true_type;
typedef __integral_constant<bool, false> __false_type;


template<typename tType>
struct remove_cv
{
    typedef tType type;
};

template<typename tType>
struct remove_cv<const tType>
{
    typedef tType type;
};

template<typename tType>
struct remove_cv<volatile tType>
{
    typedef tType type;
};

template<typename tType>
struct remove_cv<const volatile tType>
{
    typedef tType type;
};

template<typename>
struct __is_integral_helper : public __false_type{};

template<>
struct __is_integral_helper<bool> : public __true_type{};

template<>
struct __is_integral_helper<char> : public __true_type{};

template<>
struct __is_integral_helper<signed char> : public __true_type{};

template<>
struct __is_integral_helper<unsigned char> : public __true_type{};

template<>
struct __is_integral_helper<wchar_t> : public __true_type{};

template<>
struct __is_integral_helper<short> : public __true_type{};

template<>
struct __is_integral_helper<unsigned short> : public __true_type{};

template<>
struct __is_integral_helper<int> : public __true_type{};

template<>
struct __is_integral_helper<unsigned int> : public __true_type{};

template<>
struct __is_integral_helper<long> : public __true_type{};

template<>
struct __is_integral_helper<unsigned long> : public __true_type{};

template<typename tType>
struct is_integral : public __is_integral_helper<typename remove_cv<tType>::type>::type
{};

template<bool tCond, typename tType = void>
struct enable_if { };

template <class tType> 
struct enable_if<true, tType> 
{
    typedef tType type;
};

}

#endif


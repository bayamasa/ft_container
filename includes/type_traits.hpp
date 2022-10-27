#ifndef TYPE_TRAILS_HPP
# define TYPE_TRAILS_HPP

namespace ft {

template<typename tType, tType v>
struct integral_constant
{
    static const tType value = v;
    typedef tType value_type;
    typedef integral_constant<tType, v> type;
    const value_type operator()() const {
        return value;
    }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;


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
struct is_integral_helper : public false_type{};

template<>
struct is_integral_helper<bool> : public true_type{};

template<>
struct is_integral_helper<char> : public true_type{};

template<>
struct is_integral_helper<signed char> : public true_type{};

template<>
struct is_integral_helper<unsigned char> : public true_type{};

template<>
struct is_integral_helper<wchar_t> : public true_type{};

template<>
struct is_integral_helper<short> : public true_type{};

template<>
struct is_integral_helper<unsigned short> : public true_type{};

template<>
struct is_integral_helper<int> : public true_type{};

template<>
struct is_integral_helper<unsigned int> : public true_type{};

template<>
struct is_integral_helper<long> : public true_type{};

template<>
struct is_integral_helper<unsigned long> : public true_type{};

template<>
struct is_integral_helper<long long> : public true_type{};

template<>
struct is_integral_helper<unsigned long long> : public true_type{};

template<typename tType>
struct is_integral : public is_integral_helper<typename remove_cv<tType>::type>::type
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


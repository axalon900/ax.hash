//
// Created by Martin Miralles-Cordal.
// Copyright (c) 2019. All rights reserved.
//

#ifndef HASHLIB_INCLUDE_AX_HASH_IMPL_META_HPP
#define HASHLIB_INCLUDE_AX_HASH_IMPL_META_HPP

#include <functional>
#include <type_traits>

#define AX_CPP_STD __cplusplus
#define AX_CPP17 201703L
#define AX_CPP14 201402L
#define AX_CPP11 201103L
#define AX_CPP98 199711L

#if AX_CPP_STD >= AX_CPP17
    #define AX_NODISCARD [[nodiscard]]
#else
    #define AX_NODISCARD
#endif

namespace ax {

namespace _impl {

template <bool Cond, typename T = void> using if_t = typename std::enable_if<Cond, T>::type;

template<typename Type, typename...Ts> struct make_type { using type = Type; };
template<typename Type, typename...Ts> using make_type_t = typename make_type<Type, Ts...>::type;

template<typename...Ts> using bool_t = make_type_t<bool, Ts...>;
template<typename...Ts> using void_t = make_type_t<void, Ts...>;

template <typename...> struct all : std::true_type {};
template <typename B1> struct all<B1> : B1 {};
template <typename B1, typename...Bn> struct all<B1, Bn...> : std::conditional<bool(B1::value), all<Bn...>, B1>::type {};


template <typename...> struct any : std::false_type {};
template <typename B1> struct any<B1> : B1 {};
template <typename B1, typename...Bn> struct any<B1, Bn...> : std::conditional<bool(B1::value), B1, any<Bn...>>::type {};

template <class B> struct negation : std::integral_constant<bool, !bool(B::value)> {};

template <typename T, template <typename> class... Ts> using meets_all_of = all<Ts<T>...>;
template <typename T, template <typename> class... Ts> using meets_any_of = any<Ts<T>...>;
template <typename T, typename ...Ts> using all_same   = all<std::is_same<T, Ts>...>;
template <typename T, typename ...Ts> using is_any_of  = any<std::is_same<T, Ts>...>;
template <typename T, typename ...Ts> using is_none_of = negation<is_any_of<T, Ts...>>;

template<typename F, typename Tuple, size_t ...S >
constexpr decltype(auto) _apply_impl(F&& fn, Tuple&& t, std::index_sequence<S...>)
{
    return std::forward<F>(fn)(std::get<S>(std::forward<Tuple>(t))...);
}

template<typename F, typename Tuple>
constexpr decltype(auto) apply(F&& fn, Tuple&& t)
{
    constexpr auto tSize = std::tuple_size<typename std::remove_reference<Tuple>::type>::value;
    return _apply_impl(std::forward<F>(fn), std::forward<Tuple>(t), std::make_index_sequence<tSize>());
}

template <typename Range, typename Accumulator, typename BinaryOp>
constexpr Accumulator foldl(Range range, Accumulator acc, BinaryOp op)
{
auto first = std::begin(range);
for (; first != std::end(range); ++first) { acc = op(acc, *first); }
return acc;
}

template <typename T, typename = void> struct iterator_type { using type = void; };
template <class T> struct iterator_type<T, void_t<typename T::iterator>> { using type = typename T::iterator; };
template <typename T, typename = void> struct const_iterator_type { using type = void; };
template <class T> struct const_iterator_type<T, void_t<typename T::const_iterator>> { using type = typename T::const_iterator; };


template <typename T, typename Iter, typename = void>
struct is_iterator_range : std::false_type {};

template <typename T, typename Iter>
struct is_iterator_range<T, Iter, if_t<is_none_of<Iter, void>::value 
                                    && all<std::is_same<Iter, decltype(std::begin(std::declval<T>()))>,
                                           std::is_same<Iter, decltype(std::end(std::declval<T>()))>>::value>> : std::true_type {};

template <typename T>
using is_iterable = any<is_iterator_range<T, typename iterator_type<T>::type>,
        is_iterator_range<T, typename const_iterator_type<T>::type>>;

template <typename T> using is_std_hashable = std::is_default_constructible<std::hash<T>>;

template <typename E>
using is_scoped_enum = std::integral_constant<bool, std::is_enum<E>::value && !std::is_convertible<E, int>::value>;

} // namespace _impl

} // namespace ax

#endif //HASHLIB_INCLUDE_AX_HASH_IMPL_META_HPP

//
// Created by Martin Miralles-Cordal.
// Copyright (c) 2019. All rights reserved.
//

#ifndef HASHLIB_INCLUDE_AX_HASH_HASH_FUNCTIONS_HPP
#define HASHLIB_INCLUDE_AX_HASH_HASH_FUNCTIONS_HPP

#include "impl/meta.hpp"

#include <algorithm>

namespace ax {

template<typename...Ts, typename = _impl::if_t<_impl::all_same<std::size_t, Ts...>::value>>
constexpr std::size_t combine_hashes(std::size_t hash1, Ts...rest)
{
    const auto hashes = {rest...};
    return _impl::foldl(hashes, hash1, [](std::size_t hash1, std::size_t hash2) {
        return hash1 ^ (hash2 + 0x9e3779b9 + (hash1<<6u) + (hash1 >> 2u));
    });
}

/**
 * Template function object class which produces a hash value for an object of the given type.
 *
 * Like std::hash but SFINAE-friendly.
 * @tparam T The input type.
 * @tparam Enabled SFINAE typename handle.
 */
template<typename T, typename Enabled = void>
struct hash;


/**
 * Template function object class which produces a composite hash value for a series of objects of the given types.
 *
 * @tparam Ts The input types.
 */
template<typename...Ts>
struct multi_hash;

/**
 * Evaluates if the given type is usable with hash<T>.
 * @tparam T The type to check for.
 */
template<typename T> using is_hashable = std::is_default_constructible<ax::hash<T>>;

namespace hasher {

/**
 * Hash class for types which are usable with std::hash.
 * @tparam T A type for which std::hash<T> compiles and workd.
 */
template<typename T>
struct std_hash
{
    using argument_type = T;
    using result_type = std::size_t;

    constexpr result_type operator()(argument_type const &s) const noexcept { return std::hash<T>{}(s); }
};

/**
 * Hash class for scoped enum (`enum class`) types.
 * @tparam T An `enum class` type.
 */
template<typename T>
struct enum_class
{
    using argument_type = T;
    using result_type = std::size_t;

    constexpr result_type operator()(argument_type const &s) const noexcept { return static_cast<size_t>(s); }
};

/**
 * Hash class for tuple-like types (Tuple<Ts...>).
 * @tparam Tuple A tuple-like template type which supports std::get and std::tuple_size.
 *               (e.g. std::tuple, std::pair, std::array)
 * @tparam Ts The types for Tuple.
 */
template<template<typename...> class Tuple, typename...Ts>
struct tuple_like : multi_hash<Ts...>
{
    using argument_type = Tuple<Ts...>;
    using result_type = std::size_t;
    using multi_hash<Ts...>::operator();

    constexpr result_type operator()(argument_type const &s) const noexcept
    {
        return ax::_impl::apply([this](const Ts &...ts) { return (*this)(ts...); }, s);
    }
};

/**
 * Hash class for iterable containers. (e.g. std::vector, std::map, ...)
 * @tparam T The container type.
 */
template<typename T>
struct container
{
    using value_type = typename T::value_type;
    using value_hasher = hash<value_type>;
    using argument_type = T;
    using result_type = std::size_t;

    constexpr result_type operator()(argument_type const &s) const noexcept
    {
        result_type hash = 0;
        const auto begin = std::begin(s);
        const auto end = std::end(s);
        if (begin != end) {
            value_hasher hasher{};
            hash = hasher(*begin);
            const auto start = std::next(begin);
            std::for_each(start, end, [&](const value_type &elem) {
                const auto elemHash = hasher(elem);
                hash = combine_hashes(hash, elemHash);
            });
        }

        return hash;
    }
};

} // namespace hasher

/** Hash specialization for types which support use of std::hash<T>. */
template<typename T>
struct hash<T, std::enable_if_t<_impl::is_std_hashable<T>::value>> : hasher::std_hash<T> {};

/** Hash specialization for `enum class` types. */
template<typename T>
struct hash<T, std::enable_if_t<!_impl::is_std_hashable<T>::value && _impl::is_scoped_enum<T>::value>>
        : hasher::enum_class<T> {};

/** Hash specialization for container types. */
template<typename T>
struct hash<T, std::enable_if_t<!_impl::is_std_hashable<T>::value && _impl::is_iterable<T>::value>> 
        : hasher::container<T> {};

/** Base multi_hash specialization for a single type, which is simply a hash. */
template<typename T>
struct multi_hash<T> : hash<T> {};

/** Recursive multi_hash specialization for 2+ types. */
template<typename T, typename...Ts>
struct multi_hash<T, Ts...>
{
    using result_type = std::size_t;

    constexpr result_type operator()(const T &first, const Ts &...rest) const noexcept
    {
        const auto hash1 = hash<std::decay_t<T>>{}(first);
        const auto hash2 = multi_hash<std::decay_t<Ts>...>{}(rest...);
        return combine_hashes(hash1, hash2);
    }
};

} // namespace ax

#endif //HASHLIB_INCLUDE_AX_HASH_HASH_FUNCTIONS_HPP

//
// Created by Martin Miralles-Cordal.
// Copyright (c) 2019. All rights reserved.
//

#ifndef HASHLIB_INCLUDE_AX_HASH_HASH_T_HPP
#define HASHLIB_INCLUDE_AX_HASH_HASH_T_HPP

#include "hash_functions.hpp"

namespace ax {

class hash_t
{
  public:
    using result_type = std::size_t;

    constexpr hash_t() noexcept = default;
    constexpr explicit hash_t(result_type hash) noexcept : hash_(hash) {}

    template <typename T>
    constexpr explicit hash_t(T const &value) noexcept : hash_(ax::hash<T>{}(value)) {}

    constexpr void reset(result_type hash) { hash_ = hash; }

    template <typename T>
    constexpr hash_t &operator<<(T const &value) noexcept
    {
        hash_ = combine_hashes(hash_, ax::hash<T>{}(value));
        return *this;
    }

    template <typename T>
    constexpr hash_t &operator=(T const &value) noexcept
    {
        hash_ = ax::hash<T>{}(value);
        return *this;
    }

    constexpr operator result_type() const noexcept { return hash_; }

  private:
    result_type hash_{0u};
};

template <> struct hash<hash_t> : hash<hash_t::result_type> {};

} // namespace ax

#endif //HASHLIB_INCLUDE_AX_HASH_HASH_T_HPP

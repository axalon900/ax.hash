//
// Created by Martin Miralles-Cordal.
// Copyright (c) 2019. All rights reserved.
//

#ifndef AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_MEMORY_HPP
#define AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_MEMORY_HPP

#include <memory>

namespace std {

/** std::hash partial specialization for std::weak_ptr. */
template<typename T>
struct hash<weak_ptr<T>>
{
    using argument_type = weak_ptr<T>;
    using result_type = size_t;

    constexpr result_type operator()(argument_type const &s) const noexcept
    {
        auto lock = s.lock();
        return ax::hash<decltype(lock)>{}(lock);
    }
};

} // namespace std

#endif //AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_MEMORY_HPP

//
// Created by Martin Miralles-Cordal.
// Copyright (c) 2019. All rights reserved.
//

#ifndef AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_REFERENCE_WRAPPER_HPP
#define AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_REFERENCE_WRAPPER_HPP

namespace std {

/** std::hash partial specialization for std::reference_wrapper. */
template<typename T>
struct hash<reference_wrapper<T>>
{
    using argument_type = reference_wrapper<T>;
    using result_type = size_t;

    constexpr result_type operator()(argument_type const &s) const noexcept
    {
        return ax::hash<T>{}(s.get());
    }
};

} // namespace std

#endif //AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_REFERENCE_WRAPPER_HPP

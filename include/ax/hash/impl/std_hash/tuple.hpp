//
// Created by Martin Miralles-Cordal.
// Copyright (c) 2019. All rights reserved.
//

#ifndef AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_TUPLE_HPP
#define AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_TUPLE_HPP

#include <tuple>

namespace std {

/** std::hash partial specialization for std::pair. */
template<typename F, typename S>
struct hash<std::pair<F, S>> : ax::hasher::tuple_like<std::pair, F, S> {};

/** std::hash partial specialization for std::tuple. */
template<typename...Ts>
struct hash<std::tuple<Ts...>> : ax::hasher::tuple_like<std::tuple, Ts...> {};

} // namespace std

#endif //AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_TUPLE_HPP

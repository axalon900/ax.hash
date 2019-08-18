//
// Created by Martin Miralles-Cordal.
// Copyright (c) 2019. All rights reserved.
//

#ifndef AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_UNORDERED_SET_HPP
#define AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_UNORDERED_SET_HPP

#include <unordered_set>

namespace std {

/** std::hash partial specialization for std::unordered_set. */
template<typename...Ts>
struct hash<unordered_set<Ts...>> : ax::hasher::container<unordered_set<Ts...>> {};

} // namespace std

#endif //AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_UNORDERED_SET_HPP

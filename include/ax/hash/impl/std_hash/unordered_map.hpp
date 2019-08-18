//
// Created by Martin Miralles-Cordal.
// Copyright (c) 2019. All rights reserved.
//

#ifndef AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_UNORDERED_MAP_HPP
#define AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_UNORDERED_MAP_HPP

#include <unordered_map>

namespace std {

/** std::hash partial specialization for std::unordered_map. */
template<typename...Ts>
struct hash<unordered_map<Ts...>> : ax::hasher::container<unordered_map<Ts...>> {};

} // namespace std

#endif //AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_UNORDERED_MAP_HPP

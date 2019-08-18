//
// Created by Martin Miralles-Cordal.
// Copyright (c) 2019. All rights reserved.
//

#ifndef AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_MAP_HPP
#define AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_MAP_HPP

#include <map>

namespace std {

/** std::hash partial specialization for std::map. */
template<typename...Ts>
struct hash<map<Ts...>> : ax::hasher::container<map<Ts...>> {};

} // namespace std

#endif //AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_MAP_HPP

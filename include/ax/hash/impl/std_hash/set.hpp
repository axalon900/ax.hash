//
// Created by Martin Miralles-Cordal.
// Copyright (c) 2019. All rights reserved.
//

#ifndef AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_SET_HPP
#define AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_SET_HPP

#include <set>

namespace std {

/** std::hash partial specialization for std::set. */
template<typename...Ts>
struct hash<set<Ts...>> : ax::hasher::container<set<Ts...>> {};

} // namespace std

#endif //AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_SET_HPP

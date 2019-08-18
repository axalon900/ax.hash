//
// Created by Martin Miralles-Cordal.
// Copyright (c) 2019. All rights reserved.
//

#ifndef AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_VECTOR_HPP
#define AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_VECTOR_HPP

#include <vector>

namespace std {

/** std::hash partial specialization for std::vector. */
template<typename...Ts>
struct hash<vector<Ts...>> : ax::hasher::container<vector<Ts...>> {};


} // namespace std

#endif //AX_HASHLIB_INCLUDE_AX_IMPL_STD_HASH_VECTOR_HPP

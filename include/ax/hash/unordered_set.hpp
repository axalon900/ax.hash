//
// Created by Martin Miralles-Cordal.
// Copyright (c) 2019. All rights reserved.
//

#ifndef HASHLIB_INCLUDE_AX_HASH_UNORDERED_SET_HPP
#define HASHLIB_INCLUDE_AX_HASH_UNORDERED_SET_HPP

#include "hash_functions.hpp"

#include <unordered_set>

namespace ax {

/** Alias for std::unordered_set that uses ax::hash<Key> as its hasher. */
template <class Key, /* class Hash = ax::hash<Key>, */
          class KeyEqual = std::equal_to<Key>,
          class Allocator = std::allocator<Key>>
using unordered_set = std::unordered_set<Key, ax::hash<Key>, KeyEqual, Allocator>;

} // namespace ax

#endif // HASHLIB_INCLUDE_AX_HASH_UNORDERED_SET_HPP

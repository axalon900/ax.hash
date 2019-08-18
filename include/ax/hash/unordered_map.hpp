//
// Created by Martin Miralles-Cordal.
// Copyright (c) 2019. All rights reserved.
//

#ifndef HASHLIB_INCLUDE_AX_HASH_UNORDERED_MAP_HPP
#define HASHLIB_INCLUDE_AX_HASH_UNORDERED_MAP_HPP

#include "hash_functions.hpp"

#include <unordered_map>

namespace ax {

/** Alias for std::unordered_map that uses ax::hash<Key> as its hasher. */
template <class Key, class T, /* class Hash = ax::hash<Key>, */
          class KeyEqual = std::equal_to<Key>,
          class Allocator = std::allocator<std::pair<const Key, T>>>
using unordered_map = std::unordered_map<Key, T, ax::hash<Key>, KeyEqual, Allocator>;

} // namespace ax

#endif // HASHLIB_INCLUDE_AX_HASH_UNORDERED_MAP_HPP

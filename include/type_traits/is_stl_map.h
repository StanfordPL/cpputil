#ifndef CPPUTIL_TYPE_TRAITS_IS_STL_MAP_H
#define CPPUTIL_TYPE_TRAITS_IS_STL_MAP_H

#include <map>
#include <type_traits>
#include <unordered_map>

namespace cpputil {

template <typename T>
struct is_stl_map : public std::false_type {};

template <typename Key, typename T, typename Comp, typename Alloc> 
struct is_stl_map<std::map<Key, T, Comp, Alloc>> : public std::true_type {};
template <typename Key, typename T, typename Comp, typename Alloc> 
struct is_stl_map<const std::map<Key, T, Comp, Alloc>> : public std::true_type {};

template <typename Key, typename T, typename Comp, typename Alloc> 
struct is_stl_map<std::multimap<Key, T, Comp, Alloc>> : public std::true_type {};
template <typename Key, typename T, typename Comp, typename Alloc> 
struct is_stl_map<const std::multimap<Key, T, Comp, Alloc>> : public std::true_type {};

template <typename Key, typename T, typename Hash, typename Eq, typename Alloc>
struct is_stl_map<std::unordered_map<Key, T, Hash, Eq, Alloc>> : public std::true_type {};
template <typename Key, typename T, typename Hash, typename Eq, typename Alloc>
struct is_stl_map<const std::unordered_map<Key, T, Hash, Eq, Alloc>> : public std::true_type {};

template <typename Key, typename T, typename Hash, typename Eq, typename Alloc>
struct is_stl_map<std::unordered_multimap<Key, T, Hash, Eq, Alloc>> : public std::true_type {};
template <typename Key, typename T, typename Hash, typename Eq, typename Alloc>
struct is_stl_map<const std::unordered_multimap<Key, T, Hash, Eq, Alloc>> : public std::true_type {};

} // namespace cpputil

#endif


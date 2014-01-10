#ifndef CPPUTIL_TYPE_TRAITS_IS_STL_SET_H
#define CPPUTIL_TYPE_TRAITS_IS_STL_SET_H

#include <set>
#include <type_traits>
#include <unordered_set>

namespace cpputil {

template <typename T>
struct is_stl_set : public std::false_type {};

template <typename Key, typename Comp, typename Alloc> 
struct is_stl_set<std::multiset<Key, Comp, Alloc>> : public std::true_type {};
template <typename Key, typename Comp, typename Alloc> 
struct is_stl_set<const std::multiset<Key, Comp, Alloc>> : public std::true_type {};

template <typename Key, typename Comp, typename Alloc> 
struct is_stl_set<std::set<Key, Comp, Alloc>> : public std::true_type {};
template <typename Key, typename Comp, typename Alloc> 
struct is_stl_set<const std::set<Key, Comp, Alloc>> : public std::true_type {};

template <typename Key, typename Hash, typename Eq, typename Alloc>
struct is_stl_set<std::unordered_set<Key, Hash, Eq, Alloc>> : public std::true_type {};
template <typename Key, typename Hash, typename Eq, typename Alloc>
struct is_stl_set<const std::unordered_set<Key, Hash, Eq, Alloc>> : public std::true_type {};

template <typename Key, typename Hash, typename Eq, typename Alloc>
struct is_stl_set<std::unordered_multiset<Key, Hash, Eq, Alloc>> : public std::true_type {};
template <typename Key, typename Hash, typename Eq, typename Alloc>
struct is_stl_set<const std::unordered_multiset<Key, Hash, Eq, Alloc>> : public std::true_type {};

} // namespace cpputil

#endif


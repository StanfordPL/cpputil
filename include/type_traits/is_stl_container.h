#ifndef CPPUTIL_INCLUDE_TYPE_TRAITS_IS_STL_CONTAINER_H
#define CPPUTIL_INCLUDE_TYPE_TRAITS_IS_STL_CONTAINER_H

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace cpputil {

template <typename T> 
struct is_stl_container : public std::false_type {};

template <typename T, size_t N> 
struct is_stl_container<std::array<T, N>> : public std::true_type {};
template <typename T, size_t N> 
struct is_stl_container<const std::array<T, N>> : public std::true_type {};

template <typename T, typename Alloc> 
struct is_stl_container<std::deque<T, Alloc>> : public std::true_type {};
template <typename T, typename Alloc> 
struct is_stl_container<const std::deque<T, Alloc>> : public std::true_type {};

template <typename T, typename Alloc> 
struct is_stl_container<std::list<T, Alloc>> : public std::true_type {};
template <typename T, typename Alloc> 
struct is_stl_container<const std::list<T, Alloc>> : public std::true_type {};

template <typename T, typename Alloc> 
struct is_stl_container<std::forward_list<T, Alloc>> : public std::true_type {};
template <typename T, typename Alloc> 
struct is_stl_container<const std::forward_list<T, Alloc>> : public std::true_type {};

template <typename Key, typename T, typename Comp, typename Alloc> 
struct is_stl_container<std::map<Key, T, Comp, Alloc>> : public std::true_type {};
template <typename Key, typename T, typename Comp, typename Alloc> 
struct is_stl_container<const std::map<Key, T, Comp, Alloc>> : public std::true_type {};

template <typename Key, typename T, typename Comp, typename Alloc> 
struct is_stl_container<std::multimap<Key, T, Comp, Alloc>> : public std::true_type {};
template <typename Key, typename T, typename Comp, typename Alloc> 
struct is_stl_container<const std::multimap<Key, T, Comp, Alloc>> : public std::true_type {};

template <typename Key, typename Comp, typename Alloc> 
struct is_stl_container<std::multiset<Key, Comp, Alloc>> : public std::true_type {};
template <typename Key, typename Comp, typename Alloc> 
struct is_stl_container<const std::multiset<Key, Comp, Alloc>> : public std::true_type {};

template <typename Key, typename Comp, typename Alloc> 
struct is_stl_container<std::set<Key, Comp, Alloc>> : public std::true_type {};
template <typename Key, typename Comp, typename Alloc> 
struct is_stl_container<const std::set<Key, Comp, Alloc>> : public std::true_type {};

template <typename Key, typename T, typename Hash, typename Eq, typename Alloc>
struct is_stl_container<std::unordered_map<Key, T, Hash, Eq, Alloc>> : public std::true_type {};
template <typename Key, typename T, typename Hash, typename Eq, typename Alloc>
struct is_stl_container<const std::unordered_map<Key, T, Hash, Eq, Alloc>> : public std::true_type {};

template <typename Key, typename Hash, typename Eq, typename Alloc>
struct is_stl_container<std::unordered_set<Key, Hash, Eq, Alloc>> : public std::true_type {};
template <typename Key, typename Hash, typename Eq, typename Alloc>
struct is_stl_container<const std::unordered_set<Key, Hash, Eq, Alloc>> : public std::true_type {};

template <typename Key, typename T, typename Hash, typename Eq, typename Alloc>
struct is_stl_container<std::unordered_multimap<Key, T, Hash, Eq, Alloc>> : public std::true_type {};
template <typename Key, typename T, typename Hash, typename Eq, typename Alloc>
struct is_stl_container<const std::unordered_multimap<Key, T, Hash, Eq, Alloc>> : public std::true_type {};

template <typename Key, typename Hash, typename Eq, typename Alloc>
struct is_stl_container<std::unordered_multiset<Key, Hash, Eq, Alloc>> : public std::true_type {};
template <typename Key, typename Hash, typename Eq, typename Alloc>
struct is_stl_container<const std::unordered_multiset<Key, Hash, Eq, Alloc>> : public std::true_type {};

template <typename T, typename Alloc> 
struct is_stl_container<std::vector<T, Alloc>> : public std::true_type {};
template <typename T, typename Alloc> 
struct is_stl_container<const std::vector<T, Alloc>> : public std::true_type {};

} // namespace cpputil

#endif

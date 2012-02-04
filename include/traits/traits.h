#ifndef CPPUTIL_TRAITS_TRAITS_H
#define CPPUTIL_TRAITS_TRAITS_H

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <stddef.h>

namespace cpputil
{

template <typename T> 
struct is_stl_container : public std::false_type {};

template <typename T, size_t N> 
struct is_stl_container<std::array<T, N>> : public std::true_type {};

template <typename T, typename Alloc> 
struct is_stl_container<std::deque<T, Alloc>> : public std::true_type {};

template <typename T, typename Alloc> 
struct is_stl_container<std::list<T, Alloc>> : public std::true_type {};

template <typename T, typename Alloc> 
struct is_stl_container<std::forward_list<T, Alloc>> : public std::true_type {};

template <typename Key, typename T, typename Comp, typename Alloc> 
struct is_stl_container<std::map<Key, T, Comp, Alloc>> : public std::true_type {};

template <typename Key, typename T, typename Comp, typename Alloc> 
struct is_stl_container<std::multimap<Key, T, Comp, Alloc>> : public std::true_type {};

template <typename Key, typename Comp, typename Alloc> 
struct is_stl_container<std::multiset<Key, Comp, Alloc>> : public std::true_type {};

template <typename Key, typename Comp, typename Alloc> 
struct is_stl_container<std::set<Key, Comp, Alloc>> : public std::true_type {};

template <typename Key, typename T, typename Hash, typename Eq, typename Alloc>
struct is_stl_container<std::unordered_map<Key, T, Hash, Eq, Alloc>> : public std::true_type {};

template <typename Key, typename Hash, typename Eq, typename Alloc>
struct is_stl_container<std::unordered_set<Key, Hash, Eq, Alloc>> : public std::true_type {};

template <typename Key, typename T, typename Hash, typename Eq, typename Alloc>
struct is_stl_container<std::unordered_multimap<Key, T, Hash, Eq, Alloc>> : public std::true_type {};

template <typename Key, typename Hash, typename Eq, typename Alloc>
struct is_stl_container<std::unordered_multiset<Key, Hash, Eq, Alloc>> : public std::true_type {};

template <typename T, typename Alloc> 
struct is_stl_container<std::vector<T, Alloc>> : public std::true_type {};



template <typename T>
struct is_stl_adaptor : public std::false_type {};

template <typename T, typename Container>
struct is_stl_adaptor<std::stack<T, Container>> : public std::true_type {};

template <typename T, typename Container>
struct is_stl_adaptor<std::queue<T, Container>> : public std::true_type {};

template <typename T, typename Container, typename Comp>
struct is_stl_adaptor<std::priority_queue<T, Container, Comp>> : public std::true_type {};



template <typename T>
struct is_stl_sequence : public std::false_type {};

template <typename T, size_t N> 
struct is_stl_sequence<std::array<T, N>> : public std::true_type {};

template <typename T, typename Alloc> 
struct is_stl_sequence<std::deque<T, Alloc>> : public std::true_type {};

template <typename T, typename Alloc> 
struct is_stl_sequence<std::list<T, Alloc>> : public std::true_type {};

template <typename T, typename Alloc> 
struct is_stl_sequence<std::forward_list<T, Alloc>> : public std::true_type {};

template <typename T, typename Alloc> 
struct is_stl_sequence<std::vector<T, Alloc>> : public std::true_type {};



template <typename T>
struct is_stl_set : public std::false_type {};

template <typename Key, typename Comp, typename Alloc> 
struct is_stl_set<std::multiset<Key, Comp, Alloc>> : public std::true_type {};

template <typename Key, typename Comp, typename Alloc> 
struct is_stl_set<std::set<Key, Comp, Alloc>> : public std::true_type {};

template <typename Key, typename Hash, typename Eq, typename Alloc>
struct is_stl_set<std::unordered_set<Key, Hash, Eq, Alloc>> : public std::true_type {};

template <typename Key, typename Hash, typename Eq, typename Alloc>
struct is_stl_set<std::unordered_multiset<Key, Hash, Eq, Alloc>> : public std::true_type {};



template <typename T>
struct is_stl_map : public std::false_type {};

template <typename Key, typename T, typename Comp, typename Alloc> 
struct is_stl_map<std::map<Key, T, Comp, Alloc>> : public std::true_type {};

template <typename Key, typename T, typename Comp, typename Alloc> 
struct is_stl_map<std::multimap<Key, T, Comp, Alloc>> : public std::true_type {};

template <typename Key, typename T, typename Hash, typename Eq, typename Alloc>
struct is_stl_map<std::unordered_map<Key, T, Hash, Eq, Alloc>> : public std::true_type {};

template <typename Key, typename T, typename Hash, typename Eq, typename Alloc>
struct is_stl_map<std::unordered_multimap<Key, T, Hash, Eq, Alloc>> : public std::true_type {};



}

#endif

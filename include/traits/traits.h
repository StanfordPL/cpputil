#ifndef CPPUTIL_TRAITS_TRAITS_H
#define CPPUTIL_TRAITS_TRAITS_H

#include <deque>
#include <list>
#include <map>
#include <set>
#include <type_traits>
#include <vector>

namespace cpputil
{

template <typename T> 
struct is_stl_container : public std::false_type {};

template <typename T, typename Alloc> 
struct is_stl_container<std::vector<T, Alloc>> : public std::true_type {};

template <typename T, typename Alloc> 
struct is_stl_container<std::list<T, Alloc>> : public std::true_type {};

template <typename T, typename Comp, typename Alloc> 
struct is_stl_container<std::set<T, Comp, Alloc>> : public std::true_type {};

template <typename Key, typename Val, typename Comp, typename Alloc> 
struct is_stl_container<std::map<Key, Val, Comp, Alloc>> : public std::true_type {};

}

#endif

#ifndef CPPUTIL_INCLUDE_TYPE_TRAITS_IS_STL_SEQUENCE_H
#define CPPUTIL_INCLUDE_TYPE_TRAITS_IS_STL_SEQUENCE_H

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <type_traits>
#include <vector>

namespace cpputil {

template <typename T>
struct is_stl_sequence : public std::false_type {};

template <typename T, size_t N> 
struct is_stl_sequence<std::array<T, N>> : public std::true_type {};
template <typename T, size_t N> 
struct is_stl_sequence<const std::array<T, N>> : public std::true_type {};

template <typename T, typename Alloc> 
struct is_stl_sequence<std::deque<T, Alloc>> : public std::true_type {};
template <typename T, typename Alloc> 
struct is_stl_sequence<const std::deque<T, Alloc>> : public std::true_type {};

template <typename T, typename Alloc> 
struct is_stl_sequence<std::list<T, Alloc>> : public std::true_type {};
template <typename T, typename Alloc> 
struct is_stl_sequence<const std::list<T, Alloc>> : public std::true_type {};

template <typename T, typename Alloc> 
struct is_stl_sequence<std::forward_list<T, Alloc>> : public std::true_type {};
template <typename T, typename Alloc> 
struct is_stl_sequence<const std::forward_list<T, Alloc>> : public std::true_type {};

template <typename T, typename Alloc> 
struct is_stl_sequence<std::vector<T, Alloc>> : public std::true_type {};
template <typename T, typename Alloc> 
struct is_stl_sequence<const std::vector<T, Alloc>> : public std::true_type {};

} // namespace cpputil 

#endif

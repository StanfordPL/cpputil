#ifndef CPPUTIL_INCLUDE_TYPE_TRAITS_IS_STL_ADAPTOR_H
#define CPPUTIL_INCLUDE_TYPE_TRAITS_IS_STL_ADAPTOR_H

#include <stack>
#include <type_traits>
#include <queue>

namespace cpputil {

template <typename T>
struct is_stl_adaptor : public std::false_type {};

template <typename T, typename Container>
struct is_stl_adaptor<std::stack<T, Container>> : public std::true_type {};
template <typename T, typename Container>
struct is_stl_adaptor<const std::stack<T, Container>> : public std::true_type {};

template <typename T, typename Container>
struct is_stl_adaptor<std::queue<T, Container>> : public std::true_type {};
template <typename T, typename Container>
struct is_stl_adaptor<const std::queue<T, Container>> : public std::true_type {};

template <typename T, typename Container, typename Comp>
struct is_stl_adaptor<std::priority_queue<T, Container, Comp>> : public std::true_type {};
template <typename T, typename Container, typename Comp>
struct is_stl_adaptor<const std::priority_queue<T, Container, Comp>> : public std::true_type {};

} // namespace cpputil

#endif

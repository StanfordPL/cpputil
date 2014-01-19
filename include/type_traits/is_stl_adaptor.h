// Copyright 2014 eric schkufza
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

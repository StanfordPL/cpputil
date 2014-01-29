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

#ifndef CPPUTIL_INCLUDE_META_IS_STL_SEQUENCE_H
#define CPPUTIL_INCLUDE_META_IS_STL_SEQUENCE_H

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <type_traits>
#include <vector>

namespace cpputil {

template <typename T>
struct is_stl_sequence : public std::false_type { };

template <typename T, size_t N>
struct is_stl_sequence<std::array<T, N>> : public std::true_type { };

template <typename T, size_t N>
struct is_stl_sequence<const std::array<T, N>> : public std::true_type { };

template <typename T, typename Alloc>
struct is_stl_sequence<std::deque<T, Alloc>> : public std::true_type { };

template <typename T, typename Alloc>
struct is_stl_sequence<const std::deque<T, Alloc>> : public std::true_type { };

template <typename T, typename Alloc>
struct is_stl_sequence<std::list<T, Alloc>> : public std::true_type { };

template <typename T, typename Alloc>
struct is_stl_sequence<const std::list<T, Alloc>> : public std::true_type { };

template <typename T, typename Alloc>
struct is_stl_sequence<std::forward_list<T, Alloc>> : public std::true_type { };

template <typename T, typename Alloc>
struct is_stl_sequence<const std::forward_list<T, Alloc>> : public std::true_type { };

template <typename T, typename Alloc>
struct is_stl_sequence<std::vector<T, Alloc>> : public std::true_type { };

template <typename T, typename Alloc>
struct is_stl_sequence<const std::vector<T, Alloc>> : public std::true_type { };

} // namespace cpputil

#endif

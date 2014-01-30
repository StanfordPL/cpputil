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

#ifndef CPPUTIL_INCLUDE_META_CONTAINED_TYPE_H
#define CPPUTIL_INCLUDE_META_CONTAINED_TYPE_H

#include <type_traits>

#include "include/meta/is_stl_sequence.h"

namespace cpputil {

template <typename T, typename Ignore = void>
struct contained_type { };

template <typename T>
struct contained_type < T, typename std::enable_if < !is_stl_sequence<T>::value >::type {
  typedef T type;
};

template <typename T>
struct contained_type<T, typename std::enable_if<is_stl_sequence<T>::value>::type> {
  typedef typename contained_type<typename T::value_type>::type type;
};

} // namespace cpputil

#endif

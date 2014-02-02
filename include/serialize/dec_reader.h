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

#ifndef CPPUTIL_INCLUDE_SERIALIZE_DEC_READER_H
#define CPPUTIL_INCLUDE_SERIALIZE_DEC_READER_H

#include <iostream>
#include <type_traits>

namespace cpputil {

template <typename T, typename Enable = void>
struct DecReader;

template <typename T>
struct DecReader <T, typename std::enable_if <std::is_arithmetic<T>::value>::type> {
  void operator()(std::istream& is, T& t) const {
		is >> t;
  }
};

} // namespace cpputil

#endif



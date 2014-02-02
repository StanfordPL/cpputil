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

#ifndef CPPUTIL_INCLUDE_SERIALIZE_RANGE_READER_H
#define CPPUTIL_INCLUDE_SERIALIZE_RANGE_READER_H

#include <iostream>
#include <type_traits>

#include "include/serialize/range.h"
#include "include/serialize/text_reader.h"
#include "include/serialize/text_style.h"

namespace cpputil {

template <typename T, typename Range, typename Style = TextStyle<>, typename Enable = void>
struct RangeReader;

template <typename T, typename Range, typename Style>
struct RangeReader<T, Range, Style, typename std::enable_if<std::is_arithmetic<T>::value>::type> {
  void operator()(std::istream& is, T& t) const {
    TextReader<T, Style>()(is, t);
    if (t < Range::lower() || t > Range::upper()) {
      is.setstate(std::ios::failbit);
    }
  }
};

} // namespace cpputil

#endif

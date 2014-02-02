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

#ifndef CPPUTIL_INCLUDE_SERIALIZE_HEX_WRITER_H
#define CPPUTIL_INCLUDE_SERIALIZE_HEX_WRITER_H

#include <iostream>
#include <type_traits>

#include "include/meta/bit_width.h"

namespace cpputil {

template <typename T, size_t Group = 8, typename Enable = void>
struct HexWriter;

template <typename T, size_t Group>
struct HexWriter <T, Group, typename std::enable_if <std::is_arithmetic<T>::value>::type> {
  void operator()(std::ostream& os, const T& t) const {
    const auto f = os.flags(std::ios::hex);
    os.unsetf(std::ios::showbase);

    for (size_t i = bit_width<T>::value / 4; i > 0; --i) {
      if (i < bit_width<T>::value / 4 && i % Group == 0) {
        os << " ";
      }

      os << ((((uint8_t*) &t)[(i - 1) / 2] >> (i % 2 == 0 ? 4 : 0)) & 0x0f);
    }

    os.setf(f);
  }
};

} // namespace cpputil

#endif



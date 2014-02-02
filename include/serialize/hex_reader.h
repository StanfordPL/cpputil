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

#ifndef CPPUTIL_INCLUDE_SERIALIZE_HEX_READER_H
#define CPPUTIL_INCLUDE_SERIALIZE_HEX_READER_H

#include <array>
#include <cctype>
#include <iostream>
#include <type_traits>

#include "include/meta/bit_width.h"

namespace cpputil {

#define die_if(cond) \
	if (cond) { \
		is.setstate(std::ios::failbit); \
		return; \
	}

template <typename T, size_t Group = 8, typename Enable = void>
struct HexReader;

template <typename T, size_t Group>
struct HexReader <T, Group, typename std::enable_if <std::is_arithmetic<T>::value>::type> {
  void operator()(std::istream& is, T& t) const {
		std::array<uint8_t, bit_width<T>::value / 8> buffer;
		buffer.fill(0);

    for (size_t i = bit_width<T>::value / 4; i > 0; --i) {
      if (i < bit_width<T>::value / 4 && i % Group == 0) {
        die_if(is.get() != ' ');
      }
      const auto c = is.get();
      die_if(!isxdigit(c));

      const uint8_t temp = (c >= '0' && c <= '9') ? (c - '0') : (c - 'a' + 10);
      buffer[(i-1)/2] |= (temp << (i % 2 == 0 ? 4 : 0));
    }

		t = *((T*) buffer.data());
  }
};

#undef die_unless

} // namespace cpputil

#endif


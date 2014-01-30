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

template <typename T, size_t Group = 2, typename Enable = void>
struct HexReader;

template <typename T, size_t Group>
struct HexReader < T, Group, typename std::enable_if < std::is_integral<T>::value>::type> {
  void operator()(std::istream& is, T& t) const {
		t = 0;

		for (size_t i = bit_width<T>::value/4; i > 0; --i) {
			if (i < bit_width<T>::value/4 && i % Group == 0) {
				die_if(is.get() != ' ');
			} 
			const auto c = is.get();
			die_if(!isxdigit(c));
	
			const T temp = (c >= '0' && c <= '9') ? (c - '0') : (c - 'a' + 10);
			t |= (temp << (4*i-4));
		}
  }
};

#undef die_unless

} // namespace cpputil

#endif


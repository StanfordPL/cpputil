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

#ifndef CPPUTIL_INCLUDE_BITS_BIT_MANIP_H
#define CPPUTIL_INCLUDE_BITS_BIT_MANIP_H

#include <cassert>
#include <immintrin.h>
#include <stdint.h>

namespace cpputil {

template <typename T>
class BitManip;

template <>
class BitManip<uint64_t> {
 public:
  static size_t ntz(uint64_t x) {
#ifdef __BMI__
    return __builtin_ctzll(x);
#else
	// See https://graphics.stanford.edu/~seander/bithacks.html
	uint64_t res = 64; 
	x &= -((int64_t)x);
	if (x) res--;
	if (x & 0x00000000ffffffff) res -= 32;
	if (x & 0x0000ffff0000ffff) res -= 16;
	if (x & 0x00ff00ff00ff00ff) res -= 8;
	if (x & 0x0f0f0f0f0f0f0f0f) res -= 4;
	if (x & 0x3333333333333333) res -= 2;
	if (x & 0x5555555555555555) res -= 1;
	return res;
#endif
  }

	static size_t pop_count(uint64_t x) {
#ifdef __POPCNT__
		return __builtin_popcountll(x);
#else
	// See https://graphics.stanford.edu/~seander/bithacks.html
	uint64_t res = x - ((x >> 1) & 0x5555555555555555);
	res = ((res >> 2) & 0x3333333333333333) + (res & 0x3333333333333333);
	res = ((res >> 4) + res) & 0x0f0f0f0f0f0f0f0f;
	res = ((res >> 8) + res) & 0x00ff00ff00ff00ff;
	res = ((res >> 16) + res) & 0x0000ffff0000ffff;
	res = ((res >> 32) + res) & 0x00000000ffffffff;
	return res;
#endif
	}

  static uint64_t& unset_rightmost(uint64_t& x) {
#ifdef __BMI__
    return (x = _blsr_u64(x));
#else
    return (x &= (x - 1));
#endif
  }

  static uint64_t& unset_rightmost(uint64_t& x, size_t n) {
    assert(n <= 64);
    if (n == 64) {
      return (x = 0);
    } else {
      return (x &= ~((0x1ul << n) - 1));
    }
  }
};

} // namespace cpputil

#endif

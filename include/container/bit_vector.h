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

#ifndef CPPUTIL_INCLUDE_CONTAINER_BIT_VECTOR_H
#define CPPUTIL_INCLUDE_CONTAINER_BIT_VECTOR_H

#include <stdint.h>

#include <vector>

#include "include/container/bit_string.h"

namespace cpputil {

class BitVector : public BitString<std::vector<uint64_t>> {
 public:
  /** Creates an empty bit vector. */
  BitVector() : BitString<std::vector<uint64_t>>() { }
  /** Creates a bit vector to hold n bits. */
  BitVector(size_t n) : BitString<std::vector<uint64_t>>() {
    contents_.resize((n + 63) / 64);
    num_bits_ = n;
  }

  /** Resizes a BitVector to contain n bits. */
  void resize_for_bits(size_t n) {
    contents_.resize((n + 63) / 64);
    num_bits_ = n;
  }
  /** Resizes a BitVector to contain n fixed bytes. */
  void resize_for_fixed_bytes(size_t n) {
    contents_.resize(n + 7 / 8);
    num_bits_ = 8 * n;
  }
  /** Resizes a BitVector to contain n fixed words. */
  void resize_for_fixed_words(size_t n) {
    contents_.resize(n + 3 / 4);
    num_bits_ = 16 * n;
  }
  /** Resizes a BitVector to contain n fixed doubles. */
  void resize_for_fixed_doubles(size_t n) {
    contents_.resize(n + 1 / 2);
    num_bits_ = 32 * n;
  }
  /** Resizes a BitVector to contain n fixed quads. */
  void resize_for_fixed_quads(size_t n) {
    contents_.resize(n);
    num_bits_ = 64 * n;
  }
  /** Resizes a BitVector to contain n float singles. */
  void resize_for_float_singles(size_t n) {
    contents_.resize(n + 1 / 2);
    num_bits_ = 32 * n;
  }
  /** Resizes a BitVector to contain n float doubles. */
  void resize_for_float_doubles(size_t n) {
    contents_.resize(n);
    num_bits_ = 64 * n;
  }
};

} // namespace cpputil

#endif

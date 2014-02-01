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

#include <algorithm>
#include <cassert>
#include <immintrin.h>
#include <stdint.h>
#include <vector>
#include <xmmintrin.h>

namespace cpputil {

#if defined(__AVX2__) && defined(__AVX__)
#define ALIGN alignas(32)
#elif defined(__AVX__)
#define ALIGN alignas(16)
#else
#define ALIGN
#endif

class ALIGN BitVector : public std::vector<uint8_t> {
 public:
  // Inherit constructors
  using std::vector<uint8_t>::vector;

  /** Resizes this BitVector to contain n fixed bytes. */
  void resize_for_fixed_bytes(size_t n) {
    resize(n);
  }

  /** Resizes this BitVector to contain n fixed words. */
  void resize_for_fixed_words(size_t n) {
    resize(n * 2);
  }

  /** Resizes this BitVector to contain n fixed doubles. */
  void resize_for_fixed_doubles(size_t n) {
    resize(n * 4);
  }

  /** Resizes this BitVector to contain n fixed quads. */
  void resize_for_fixed_quads(size_t n) {
    resize(n * 8);
  }

  /** Resizes this BitVector to contain n float singles. */
  void resize_for_float_singles(size_t n) {
    resize(n * 4);
  }

  /** Resizes this BitVector to contain n float doubles. */
  void resize_for_float_doubles(size_t n) {
    resize(n * 8);
  }

  /** Returns the number of bytes in this array. */
  size_t num_fixed_bytes() const {
    return size();
  }

  /** Returns the number of words in this array. */
  size_t num_fixed_words() const {
    return size() / 2;
  }

  /** Returns the number of doubles in this array. */
  size_t num_fixed_doubles() const {
    return size() / 4;
  }

  /** Returns the number of quads in this array. */
  size_t num_fixed_quads() const {
    return size() / 8;
  }

  /** Returns the number of floats in this array. */
  size_t num_float_singles() const {
    return size() / 4;
  }

  /** Returns the number of doubles in this array. */
  size_t num_float_doubles() const {
    return size() / 8;
  }

  /** Returns a fixed point byte value. */
  uint8_t& get_fixed_byte(size_t i) {
    assert(i < num_fixed_bytes());
    return ((uint8_t*) &*begin())[i];
  }

  /** Returns a fixed point word value. */
  uint16_t& get_fixed_word(size_t i) {
    assert(i < num_fixed_words());
    return ((uint16_t*) &*begin())[i];
  }

  /** Returns a fixed point double value. */
  uint32_t& get_fixed_double(size_t i) {
    assert(i < num_fixed_doubles());
    return ((uint32_t*) &*begin())[i];
  }

  /** Returns a fixed point quad value. */
  uint64_t& get_fixed_quad(size_t i) {
    assert(i < num_fixed_quads());
    return ((uint64_t*) &*begin())[i];
  }

  /** Returns a single precision floating point value. */
  float& get_float_single(size_t i) {
    assert(i < num_float_singles());
    return ((float*) &*begin())[i];
  }

  /** Returns a double precision floating point value. */
  double& get_float_double(size_t i) {
    assert(i < num_float_doubles());
    return ((double*) &*begin())[i];
  }

  /** Returns a const fixed point byte value. */
  uint8_t get_fixed_byte(size_t i) const {
    assert(i < num_fixed_bytes());
    return ((uint8_t*) &*begin())[i];
  }

  /** Returns a const fixed point word value. */
  uint16_t get_fixed_word(size_t i) const {
    assert(i < num_fixed_words());
    return ((uint16_t*) &*begin())[i];
  }

  /** Returns a const fixed point double value. */
  uint32_t get_fixed_double(size_t i) const {
    assert(i < num_fixed_doubles());
    return ((uint32_t*) &*begin())[i];
  }

  /** Returns a const fixed point quad value. */
  uint64_t get_fixed_quad(size_t i) const {
    assert(i < num_fixed_quads());
    return ((uint64_t*) &*begin())[i];
  }

  /** Returns a const single precision floating point value. */
  float get_float_single(size_t i) const {
    assert(i < num_float_singles());
    return ((float*) &*begin())[i];
  }

  /** Returns a const double precision floating point value. */
  double get_float_double(size_t i) const {
    assert(i < num_float_doubles());
    return ((double*) &*begin())[i];
  }

  /** Bit-wise and for as many bytes as possible. */
  BitVector& operator&=(const BitVector& rhs) {
    const auto n = std::min(size(), rhs.size());
    auto i = 0;

#if defined(__AVX2__) && defined(__AVX__)
    for (; i + 32 <= n; i += 32) {
      auto x = _mm256_load_si256((__m256i*) & (*this)[i]);
      auto y = _mm256_load_si256((__m256i*) &rhs[i]);
      x = _mm256_and_si256(x, y);
      _mm256_store_si256((__m256i*)(&(*this)[i], x);
    }
#elif defined(__AVX__)
    for (; i + 16 <= n; i += 16) {
      auto x = _mm_load_si128((__m128i*) & (*this)[i]);
      auto y = _mm_load_si128((__m128i*) &rhs[i]);
      x = _mm_and_si128(x, y);
      _mm_store_si128((__m128i*) & (*this)[i]), x);
    }
#endif

    for (; i + 8 <= n; i += 8) {
      get_fixed_quad(i / 8) &= rhs.get_fixed_quad(i / 8);
    }
    for (; i + 4 <= n; i += 4) {
      get_fixed_double(i / 4) &= rhs.get_fixed_double(i / 4);
    }
    for (; i + 2 <= n; i += 2) {
      get_fixed_word(i / 2) &= rhs.get_fixed_word(i / 2);
    }
    if (i < n) {
      get_fixed_byte(i) &= rhs.get_fixed_byte(i);
    }

    return *this;
  }

  /** Bit-wise and for as many bytes as possible. */
  BitVector operator&(const BitVector& rhs) const {
    auto ret = *this;
    return ret += rhs;
  }

  /** Bit-wise and for as many bytes as possible. */
  BitVector operator&(BitVector&& rhs) const {
    auto ret = BitVector(std::move(rhs));
    return ret += *this;
  }

  /** Bit-wise or for as many bytes as possible. */
  BitVector& operator|=(const BitVector& rhs) {
    const auto n = std::min(size(), rhs.size());
    auto i = 0;

#if defined(__AVX2__) && defined(__AVX__)
    for (; i + 32 <= n; i += 32) {
      auto x = _mm256_load_si256((__m256i*) & (*this)[i]);
      auto y = _mm256_load_si256((__m256i*) &rhs[i]);
      x = _mm256_or_si256(x, y);
      _mm256_store_si256((__m256i*)(&(*this)[i], x);
    }
#elif defined(__AVX__)
    for (; i + 16 <= n; i += 16) {
      auto x = _mm_load_si128((__m128i*) & (*this)[i]);
      auto y = _mm_load_si128((__m128i*) &rhs[i]);
      x = _mm_or_si128(x, y);
      _mm_store_si128((__m128i*) & (*this)[i]), x);
    }
#endif

    for (; i + 8 <= n; i += 8) {
      get_fixed_quad(i / 8) |= rhs.get_fixed_quad(i / 8);
    }
    for (; i + 4 <= n; i += 4) {
      get_fixed_double(i / 4) |= rhs.get_fixed_double(i / 4);
    }
    for (; i + 2 <= n; i += 2) {
      get_fixed_word(i / 2) |= rhs.get_fixed_word(i / 2);
    }
    if (i < n) {
      get_fixed_byte(i) |= rhs.get_fixed_byte(i);
    }

    return *this;
  }

  /** Bit-wise or for as many bytes as possible. */
  BitVector operator|(const BitVector& rhs) const {
    auto ret = *this;
    return ret |= rhs;
  }

  /** Bit-wise or for as many bytes as possible. */
  BitVector operator|(BitVector&& rhs) const {
    auto ret = BitVector(std::move(rhs));
    return ret |= *this;
  }

  /** Bit-wise xor for as many bytes as possible. */
  BitVector& operator^=(const BitVector& rhs) {
    const auto n = std::min(size(), rhs.size());
    auto i = 0;

#if defined(__AVX2__) && defined(__AVX__)
    for (; i + 32 <= n ; i += 32) {
      auto x = _mm256_load_si256((__m256i*) & (*this)[i]);
      auto y = _mm256_load_si256((__m256i*) &rhs[i]);
      x = _mm256_xor_si256(x, y);
      _mm256_store_si256((__m256i*)(&(*this)[i], x);
    }
#elif defined(__AVX__)
    for (; i + 16 <= n ; i += 16) {
      auto x = _mm_load_si128((__m128i*) & (*this)[i]);
      auto y = _mm_load_si128((__m128i*) &rhs[i]);
      x = _mm_xor_si128(x, y);
      _mm_store_si128((__m128i*) & (*this)[i]), x);
    }
#endif

    for (; i + 8 <= n; i += 8) {
      get_fixed_quad(i / 8) ^= rhs.get_fixed_quad(i / 8);
    }
    for (; i + 4 <= n; i += 4) {
      get_fixed_double(i / 4) ^= rhs.get_fixed_double(i / 4);
    }
    for (; i + 2 <= n; i += 2) {
      get_fixed_word(i / 2) ^= rhs.get_fixed_word(i / 2);
    }
    if (i < n) {
      get_fixed_byte(i) ^= rhs.get_fixed_byte(i);
    }

    return *this;
  }

  /** Bit-wise xor for as many bytes as possible. */
  BitVector operator^(const BitVector& rhs) const {
    auto ret = *this;
    return ret ^= rhs;
  }

  /** Bit-wise xor for as many bytes as possible. */
  BitVector operator^(BitVector&& rhs) const {
    auto ret = BitVector(std::move(rhs));
    return ret ^= *this;
  }

  /** Bit-wise not. */
  BitVector operator~() const {
    auto ret = *this;
    auto i = 0;

    // Any good ideas for how to vectorize this effectively?

    for (; i + 8 <= size(); i += 8) {
      ret.get_fixed_quad(i / 8) = ~ret.get_fixed_quad(i / 8);
    }
    for (; i + 4 <= size(); i += 4) {
      ret.get_fixed_double(i / 4) = ~ret.get_fixed_double(i / 4);
    }
    for (; i + 2 <= size(); i += 2) {
      ret.get_fixed_word(i / 2) = ~ret.get_fixed_word(i / 2);
    }
    if (i < size()) {
      ret.get_fixed_byte(i) = ~ret.get_fixed_byte(i);
    }

    return ret;
  }

  /** Concatenation. */
  BitVector& operator+=(const BitVector& rhs) {
    const auto n = size();
    resize(n + rhs.size());
    std::copy(rhs.begin(), rhs.end(), begin() + n);

    return *this;
  }

  /** Concatenation. */
  BitVector operator+(const BitVector& rhs) {
    auto ret = *this;
    return ret += rhs;
  }

  /** Concatenation. */
  BitVector operator+(BitVector&& rhs) {
    auto ret = BitVector(std::move(rhs));
    return ret += *this;
  }
};

#undef ALIGN

} // namespace cpputil

#endif

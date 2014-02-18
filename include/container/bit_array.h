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

#ifndef CPPUTIL_INCLUDE_CONTAINER_BIT_ARRAY_H
#define CPPUTIL_INCLUDE_CONTAINER_BIT_ARRAY_H

#include <algorithm>
#include <array>
#include <cassert>
#include <immintrin.h>
#include <stdint.h>
#include <xmmintrin.h>

namespace cpputil {

#if defined(__AVX2__) && defined(__AVX__)
#define ALIGN alignas(32)
#elif defined(__AVX__)
#define ALIGN alignas(16)
#else
#define ALIGN
#endif

template <size_t N>
class ALIGN BitArray : public std::array<uint8_t, N> {
 public:
  // Inherit constructors
  using std::array<uint8_t, N>::array;

  /** Returns the number of bytes in this array. */
  constexpr size_t num_fixed_bytes() {
    return N;
  }

  /** Returns the number of words in this array. */
  constexpr size_t num_fixed_words() {
    return N / 2;
  }

  /** Returns the number of doubles in this array. */
  constexpr size_t num_fixed_doubles() {
    return N / 4;
  }

  /** Returns the number of quads in this array. */
  constexpr size_t num_fixed_quads() {
    return N / 8;
  }

  /** Returns the number of floats in this array. */
  constexpr size_t num_float_singles() {
    return N / 4;
  }

  /** Returns the number of doubles in this array. */
  constexpr size_t num_float_doubles() {
    return N / 8;
  }

  /** Returns a fixed point byte value. */
  uint8_t& get_fixed_byte(size_t i) {
    assert(i < num_fixed_bytes());
    return ((uint8_t*) this->begin())[i];
  }

  /** Returns a fixed point word value. */
  uint16_t& get_fixed_word(size_t i) {
    assert(i < num_fixed_words());
    return ((uint16_t*) this->begin())[i];
  }

  /** Returns a fixed point double value. */
  uint32_t& get_fixed_double(size_t i) {
    assert(i < num_fixed_doubles());
    return ((uint32_t*) this->begin())[i];
  }

  /** Returns a fixed point quad value. */
  uint64_t& get_fixed_quad(size_t i) {
    assert(i < num_fixed_quads());
    return ((uint64_t*) this->begin())[i];
  }

  /** Returns a single precision floating point value. */
  float& get_float_single(size_t i) {
    assert(i < num_float_singles());
    return ((float*) this->begin())[i];
  }

  /** Returns a double precision floating point value. */
  double& get_float_double(size_t i) {
    assert(i < num_float_doubles());
    return ((double*) this->begin())[i];
  }

  /** Returns a const fixed point byte value. */
  uint8_t get_fixed_byte(size_t i) const {
    assert(i < num_fixed_bytes());
    return ((uint8_t*) this->begin())[i];
  }

  /** Returns a const fixed point word value. */
  uint16_t get_fixed_word(size_t i) const {
    assert(i < num_fixed_words());
    return ((uint16_t*) this->begin())[i];
  }

  /** Returns a const fixed point double value. */
  uint32_t get_fixed_double(size_t i) const {
    assert(i < num_fixed_doubles());
    return ((uint32_t*) this->begin())[i];
  }

  /** Returns a const fixed point quad value. */
  uint64_t get_fixed_quad(size_t i) const {
    assert(i < num_fixed_quads());
    return ((uint64_t*) this->begin())[i];
  }

  /** Returns a const single precision floating point value. */
  float get_float_single(size_t i) const {
    assert(i < num_float_singles());
    return ((float*) this->begin())[i];
  }

  /** Returns a const double precision floating point value. */
  double get_float_double(size_t i) const {
    assert(i < num_float_doubles());
    return ((double*) this->begin())[i];
  }

  /** Bit-wise and. */
  BitArray& operator&=(const BitArray& rhs) {
    auto i = 0;

#if defined(__AVX2__) && defined(__AVX__)
    for (; i + 32 <= N ; i += 32) {
      auto x = _mm256_load_si256((__m256i*) & (*this)[i]);
      auto y = _mm256_load_si256((__m256i*) &rhs[i]);
      x = _mm256_and_si256(x, y);
      _mm256_store_si256((__m256i*)(&(*this)[i]), x);
    }
#elif defined(__AVX__)
    for (; i + 16 <= N ; i += 16) {
      auto x = _mm_load_si128((__m128i*) & (*this)[i]);
      auto y = _mm_load_si128((__m128i*) &rhs[i]);
      x = _mm_and_si128(x, y);
      _mm_store_si128((__m128i*)(&(*this)[i]), x);
    }
#endif

    for (; i + 8 <= N; i += 8) {
      get_fixed_quad(i / 8) &= rhs.get_fixed_quad(i / 8);
    }
    for (; i + 4 <= N; i += 4) {
      get_fixed_double(i / 4) &= rhs.get_fixed_double(i / 4);
    }
    for (; i + 2 <= N; i += 2) {
      get_fixed_word(i / 2) &= rhs.get_fixed_word(i / 2);
    }
    if (i < N) {
      get_fixed_byte(i) &= rhs.get_fixed_byte(i);
    }

    return *this;
  }

  /** Bit-wise and. */
  BitArray operator&(const BitArray& rhs) const {
    auto ret = *this;
    return ret += rhs;
  }

  /** Bit-wise and. */
  BitArray operator&(BitArray&& rhs) const {
    auto ret = BitArray(std::move(rhs));
    return ret += *this;
  }

  /** Bit-wise or. */
  BitArray& operator|=(const BitArray& rhs) {
    auto i = 0;

#if defined(__AVX2__) && defined(__AVX__)
    for (; i + 32 <= N ; i += 32) {
      auto x = _mm256_load_si256((__m256i*) & (*this)[i]);
      auto y = _mm256_load_si256((__m256i*) &rhs[i]);
      x = _mm256_or_si256(x, y);
      _mm256_store_si256((__m256i*)(&(*this)[i]), x);
    }
#elif defined(__AVX__)
    for (; i + 16 <= N ; i += 16) {
      auto x = _mm_load_si128((__m128i*) & (*this)[i]);
      auto y = _mm_load_si128((__m128i*) &rhs[i]);
      x = _mm_or_si128(x, y);
      _mm_store_si128((__m128i*)(&(*this)[i]), x);
    }
#endif

    for (; i + 8 <= N; i += 8) {
      get_fixed_quad(i / 8) |= rhs.get_fixed_quad(i / 8);
    }
    for (; i + 4 <= N; i += 4) {
      get_fixed_double(i / 4) |= rhs.get_fixed_double(i / 4);
    }
    for (; i + 2 <= N; i += 2) {
      get_fixed_word(i / 2) |= rhs.get_fixed_word(i / 2);
    }
    if (i < N) {
      get_fixed_byte(i) |= rhs.get_fixed_byte(i);
    }

    return *this;
  }

  /** Bit-wise or. */
  BitArray operator|(const BitArray& rhs) const {
    auto ret = *this;
    return ret |= rhs;
  }

  /** Bit-wise or. */
  BitArray operator|(BitArray&& rhs) const {
    auto ret = BitArray(std::move(rhs));
    return ret |= *this;
  }

  /** Bit-wise xor. */
  BitArray& operator^=(const BitArray& rhs) {
    auto i = 0;

#if defined(__AVX2__) && defined(__AVX__)
    for (; i + 32 <= N ; i += 32) {
      auto x = _mm256_load_si256((__m256i*) & (*this)[i]);
      auto y = _mm256_load_si256((__m256i*) &rhs[i]);
      x = _mm256_xor_si256(x, y);
      _mm256_store_si256((__m256i*)(&(*this)[i]), x);
    }
#elif defined(__AVX__)
    for (; i + 16 <= N ; i += 16) {
      auto x = _mm_load_si128((__m128i*) & (*this)[i]);
      auto y = _mm_load_si128((__m128i*) &rhs[i]);
      x = _mm_xor_si128(x, y);
      _mm_store_si128((__m128i*)(&(*this)[i]), x);
    }
#endif

    for (; i + 8 <= N; i += 8) {
      get_fixed_quad(i / 8) ^= rhs.get_fixed_quad(i / 8);
    }
    for (; i + 4 <= N; i += 4) {
      get_fixed_double(i / 4) ^= rhs.get_fixed_double(i / 4);
    }
    for (; i + 2 <= N; i += 2) {
      get_fixed_word(i / 2) ^= rhs.get_fixed_word(i / 2);
    }
    if (i < N) {
      get_fixed_byte(i) ^= rhs.get_fixed_byte(i);
    }

    return *this;
  }

  /** Bit-wise xor. */
  BitArray operator^(const BitArray& rhs) const {
    auto ret = *this;
    return ret ^= rhs;
  }

  /** Bit-wise xor. */
  BitArray operator^(BitArray&& rhs) const {
    auto ret = BitArray(std::move(rhs));
    return ret ^= *this;
  }

  /** Bit-wise not. */
  BitArray operator~() const {
    auto ret = *this;
    auto i = 0;

    // Any good ideas for how to vectorize this effectively?

    for (; i + 8 <= N; i += 8) {
      ret.get_fixed_quad(i / 8) = ~ret.get_fixed_quad(i / 8);
    }
    for (; i + 4 <= N; i += 4) {
      ret.get_fixed_double(i / 4) = ~ret.get_fixed_double(i / 4);
    }
    for (; i + 2 <= N; i += 2) {
      ret.get_fixed_word(i / 2) = ~ret.get_fixed_word(i / 2);
    }
    if (i < N) {
      ret.get_fixed_byte(i) = ~ret.get_fixed_byte(i);
    }

    return ret;
  }

  /** Concatenation. */
  template <size_t M>
  BitArray < N + M > operator+(const BitArray<M>& rhs) const {
    BitArray < N + M > ret;
    std::copy(this->begin(), this->end(), ret.begin());
    std::copy(rhs.begin(), rhs.end(), ret.begin() + N);

    return ret;
  }
};

#undef ALIGN

} // namespace cpputil

#endif

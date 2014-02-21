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

#ifndef CPPUTIL_INCLUDE_CONTAINER_BIT_STRING_H
#define CPPUTIL_INCLUDE_CONTAINER_BIT_STRING_H

#include <cassert>
#include <stdint.h>

#include <algorithm>
#include <array>
#include <immintrin.h>
#include <type_traits>
#include <xmmintrin.h>

namespace cpputil {

#if defined(__AVX2__) && defined(__AVX__)
#define ALIGN alignas(32)
#elif defined(__AVX__)
#define ALIGN alignas(16)
#else
#define ALIGN
#endif

/** This is a generic bit string class which can be backed by a sequence of uint8_ts */
template <typename T>
class ALIGN BitString {
 public:
	typedef uint8_t* byte_iterator;
	typedef const uint8_t* const_byte_iterator;

	/** Default constructor. */
	BitString() : contents_() { }
	/** Copy constructor. */
	BitString(const BitString& rhs) {
		contents_ = rhs.contents_;
	}
	/** Move constructor. */
	BitString(BitString&& rhs) {
		contents_ = std::move(rhs.contents_);	
	}
	/** Assignment operator. */
	BitString& operator=(const BitString& rhs) {
		BitString(rhs).swap(*this);
		return *this;
	}
	/** Move assignment operator. */
	BitString& operator=(const BitString&& rhs) {
		BitString(std::move(rhs)).swap(*this);
		return *this;
	}

	/** Returns the number of bits in this array. */
	size_t num_bits() const {
		// Whatever the underlying sequence is, it will contain uint8_ts
		return 8 * contents_.size();
	}
  /** Returns the number of bytes in this array. */
  size_t num_fixed_bytes() const {
		// Whatever the underlying sequence is, it will contain uint8_ts
    return contents_.size();
  }
  /** Returns the number of words in this array. */
  size_t num_fixed_words() const {
    return num_fixed_bytes() / 2;
  }
  /** Returns the number of doubles in this array. */
  size_t num_fixed_doubles() const {
    return num_fixed_bytes() / 4;
  }
  /** Returns the number of quads in this array. */
  size_t num_fixed_quads() const {
    return num_fixed_bytes() / 8;
  }
  /** Returns the number of floats in this array. */
  size_t num_float_singles() const {
    return num_fixed_bytes() / 4;
  }
  /** Returns the number of doubles in this array. */
  size_t num_float_doubles() const {
    return num_fixed_bytes() / 8;
  }

  /** Returns a fixed point byte value. */
  uint8_t& get_fixed_byte(size_t i) {
    assert(i < num_fixed_bytes());
    return ((uint8_t*) contents_.data())[i];
  }
  /** Returns a fixed point word value. */
  uint16_t& get_fixed_word(size_t i) {
    assert(i < num_fixed_words());
    return ((uint16_t*) contents_.data())[i];
  }
  /** Returns a fixed point double value. */
  uint32_t& get_fixed_double(size_t i) {
    assert(i < num_fixed_doubles());
    return ((uint32_t*) contents_.data())[i];
  }
  /** Returns a fixed point quad value. */
  uint64_t& get_fixed_quad(size_t i) {
    assert(i < num_fixed_quads());
    return ((uint64_t*) contents_.data())[i];
  }
  /** Returns a single precision floating point value. */
  float& get_float_single(size_t i) {
    assert(i < num_float_singles());
    return ((float*) contents_.data())[i];
  }
  /** Returns a double precision floating point value. */
  double& get_float_double(size_t i) {
    assert(i < num_float_doubles());
    return ((double*) contents_.data())[i];
  }

	/** Returns a const bool value. */
	bool get_bit(size_t i) const {
		return contents_[i/8] & (0x00000001 << (i%8));
	}
  /** Returns a const fixed point byte value. */
  uint8_t get_fixed_byte(size_t i) const {
    assert(i < num_fixed_bytes());
    return ((uint8_t*) contents_.data())[i];
  }
  /** Returns a const fixed point word value. */
  uint16_t get_fixed_word(size_t i) const {
    assert(i < num_fixed_words());
    return ((uint16_t*) contents_.data())[i];
  }
  /** Returns a const fixed point double value. */
  uint32_t get_fixed_double(size_t i) const {
    assert(i < num_fixed_doubles());
    return ((uint32_t*) contents_.data())[i];
  }
  /** Returns a const fixed point quad value. */
  uint64_t get_fixed_quad(size_t i) const {
    assert(i < num_fixed_quads());
    return ((uint64_t*) contents_.data())[i];
  }
  /** Returns a const single precision floating point value. */
  float get_float_single(size_t i) const {
    assert(i < num_float_singles());
    return ((float*) contents_.data())[i];
  }
  /** Returns a const double precision floating point value. */
  double get_float_double(size_t i) const {
    assert(i < num_float_doubles());
    return ((double*) contents_.data())[i];
  }

	/** Byte iterator. */
	byte_iterator byte_begin() { 
		return (uint8_t*) contents_.data();
	}
	/** Byte iterator. */
	byte_iterator byte_end() {
		return (uint8_t*) contents_.data() + num_fixed_bytes();
	}
	/** Byte iterator. */
	const_byte_iterator byte_begin() const { 
		return (uint8_t*) contents_.data();
	}
	/** Byte iterator. */
	const_byte_iterator byte_end() const {
		return (uint8_t*) contents_.data() + num_fixed_bytes();
	}

  /** Bit-wise and. */
  BitString& operator&=(const BitString& rhs) {
    auto i = 0;

#if defined(__AVX2__) && defined(__AVX__)
    for (; i + 32 <= num_fixed_bytes(); i += 32) {
      auto x = _mm256_load_si256((__m256i*) &contents_[i]);
      auto y = _mm256_load_si256((__m256i*) &rhs.contents_[i]);
      x = _mm256_and_si256(x, y);
      _mm256_store_si256((__m256i*)&contents_[i], x);
    }
#elif defined(__AVX__)
    for (; i + 16 <= num_fixed_bytes(); i += 16) {
      auto x = _mm_load_si128((__m128i*) &contents_[i]);
      auto y = _mm_load_si128((__m128i*) &rhs.contents_[i]);
      x = _mm_and_si128(x, y);
      _mm_store_si128((__m128i*)&contents_[i], x);
    }
#endif

    for (; i + 8 <= num_fixed_bytes(); i += 8) {
      get_fixed_quad(i / 8) &= rhs.get_fixed_quad(i / 8);
    }
    for (; i + 4 <= num_fixed_bytes(); i += 4) {
      get_fixed_double(i / 4) &= rhs.get_fixed_double(i / 4);
    }
    for (; i + 2 <= num_fixed_bytes(); i += 2) {
      get_fixed_word(i / 2) &= rhs.get_fixed_word(i / 2);
    }
    if (i < num_fixed_bytes()) {
      get_fixed_byte(i) &= rhs.get_fixed_byte(i);
    }

    return *this;
  }
  /** Bit-wise and. */
  BitString operator&(const BitString& rhs) const {
    auto ret = *this;
    return ret += rhs;
  }
  /** Bit-wise and. */
  BitString operator&(BitString&& rhs) const {
    auto ret = BitString(std::move(rhs));
    return ret += *this;
  }

  /** Bit-wise or. */
  BitString& operator|=(const BitString& rhs) {
    auto i = 0;

#if defined(__AVX2__) && defined(__AVX__)
    for (; i + 32 <= num_fixed_bytes() ; i += 32) {
      auto x = _mm256_load_si256((__m256i*) &contents_[i]);
      auto y = _mm256_load_si256((__m256i*) &rhs.contents_[i]);
      x = _mm256_or_si256(x, y);
      _mm256_store_si256((__m256i*)&contents_[i], x);
    }
#elif defined(__AVX__)
    for (; i + 16 <= num_fixed_bytes() ; i += 16) {
      auto x = _mm_load_si128((__m128i*) &contents_[i]);
      auto y = _mm_load_si128((__m128i*) &rhs.contents_[i]);
      x = _mm_or_si128(x, y);
      _mm_store_si128((__m128i*)&contents_[i], x);
    }
#endif

    for (; i + 8 <= num_fixed_bytes(); i += 8) {
      get_fixed_quad(i / 8) |= rhs.get_fixed_quad(i / 8);
    }
    for (; i + 4 <= num_fixed_bytes(); i += 4) {
      get_fixed_double(i / 4) |= rhs.get_fixed_double(i / 4);
    }
    for (; i + 2 <= num_fixed_bytes(); i += 2) {
      get_fixed_word(i / 2) |= rhs.get_fixed_word(i / 2);
    }
    if (i < num_fixed_bytes()) {
      get_fixed_byte(i) |= rhs.get_fixed_byte(i);
    }

    return *this;
  }
  /** Bit-wise or. */
  BitString operator|(const BitString& rhs) const {
    auto ret = *this;
    return ret |= rhs;
  }
  /** Bit-wise or. */
  BitString operator|(BitString&& rhs) const {
    auto ret = BitString(std::move(rhs));
    return ret |= *this;
  }

  /** Bit-wise xor. */
  BitString& operator^=(const BitString& rhs) {
    auto i = 0;

#if defined(__AVX2__) && defined(__AVX__)
    for (; i + 32 <= num_fixed_bytes() ; i += 32) {
      auto x = _mm256_load_si256((__m256i*) &contents_[i]);
      auto y = _mm256_load_si256((__m256i*) &rhs.contents_[i]);
      x = _mm256_xor_si256(x, y);
      _mm256_store_si256((__m256i*)&contents_[i], x);
    }
#elif defined(__AVX__)
    for (; i + 16 <= num_fixed_bytes() ; i += 16) {
      auto x = _mm_load_si128((__m128i*) &contents_[i]);
      auto y = _mm_load_si128((__m128i*) &rhs.contents_[i]);
      x = _mm_xor_si128(x, y);
      _mm_store_si128((__m128i*)&contents_[i], x);
    }
#endif

    for (; i + 8 <= num_fixed_bytes(); i += 8) {
      get_fixed_quad(i / 8) ^= rhs.get_fixed_quad(i / 8);
    }
    for (; i + 4 <= num_fixed_bytes(); i += 4) {
      get_fixed_double(i / 4) ^= rhs.get_fixed_double(i / 4);
    }
    for (; i + 2 <= num_fixed_bytes(); i += 2) {
      get_fixed_word(i / 2) ^= rhs.get_fixed_word(i / 2);
    }
    if (i < num_fixed_bytes()) {
      get_fixed_byte(i) ^= rhs.get_fixed_byte(i);
    }

    return *this;
  }
  /** Bit-wise xor. */
  BitString operator^(const BitString& rhs) const {
    auto ret = *this;
    return ret ^= rhs;
  }
  /** Bit-wise xor. */
  BitString operator^(BitString&& rhs) const {
    auto ret = BitString(std::move(rhs));
    return ret ^= *this;
  }
  /** Bit-wise not. */
  BitString operator~() const {
    auto ret = *this;
    auto i = 0;

    // Any good ideas for how to vectorize this effectively?

    for (; i + 8 <= num_fixed_bytes(); i += 8) {
      ret.get_fixed_quad(i / 8) = ~ret.get_fixed_quad(i / 8);
    }
    for (; i + 4 <= num_fixed_bytes(); i += 4) {
      ret.get_fixed_double(i / 4) = ~ret.get_fixed_double(i / 4);
    }
    for (; i + 2 <= num_fixed_bytes(); i += 2) {
      ret.get_fixed_word(i / 2) = ~ret.get_fixed_word(i / 2);
    }
    if (i < num_fixed_bytes()) {
      ret.get_fixed_byte(i) = ~ret.get_fixed_byte(i);
    }

    return ret;
  }

	/** STL-compliant swap. */
	void swap(BitString& rhs) {
		contents_.swap(rhs.contents_);
	}

 protected:
	T contents_;
};

#undef ALIGN

} // namespace cpputil

namespace std {

/** STL-compliant swap. */
template <typename T>
void swap(cpputil::BitString<T>& lhs, cpputil::BitString<T>& rhs) {
	lhs.swap(rhs);
}

} // namespace 

#endif

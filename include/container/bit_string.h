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
#include <xmmintrin.h>

#include "include/bits/bit_manip.h"

namespace cpputil {

template <typename T>
class BitString {
 public:
  class const_set_bit_index_iterator {
    friend class BitString;

   public:
    /** Return the index of the current set bit. */
    size_t operator*() const {
      return index_;
    }
    /** Increment. */
    const_set_bit_index_iterator& operator++() {
      BitManip<uint64_t>::unset_rightmost(index_, 6);
      if (BitManip<uint64_t>::unset_rightmost(current_) == 0) {
        const auto old_itr = itr_;
        for (++itr_; itr_ != end_ && *itr_ == 0; ++itr_);
        index_ += 64 * (itr_ - old_itr);
        current_ = *itr_;
      }
      index_ += BitManip<uint64_t>::ntz(current_);
      index_ = std::min(num_bits_, index_);
      return *this;
    }
    /** Equality. */
    bool operator==(const const_set_bit_index_iterator& rhs) const {
      return index_ == rhs.index_;
    }
    /** Inequality. */
    bool operator!=(const const_set_bit_index_iterator& rhs) const {
      return index_ != rhs.index_;
    }

   private:
    /** Constructor. */
    const_set_bit_index_iterator(typename T::const_iterator i, typename T::const_iterator begin,
                                 typename T::const_iterator end, size_t num_bits) :
      end_(end), num_bits_(num_bits) {
      for (itr_ = i; itr_ != end_ && *itr_ == 0; ++itr_);
      current_ = *itr_;
      index_ = 64 * (itr_ - begin) + BitManip<uint64_t>::ntz(current_);
      index_ = std::min(num_bits_, index_);
    }

    size_t index_;
    typename T::const_iterator itr_;
    typename T::const_iterator end_;
    size_t num_bits_;
    uint64_t current_;
  };

  template <typename S>
  class const_set_index_iterator {
    friend class BitString;

   public:
    /** Return the index of the current set value. */
    size_t operator*() const {
      return index_;
    }
    /** Increment. */
    const_set_index_iterator& operator++() {
      const auto old_itr = itr_;
      for (++itr_; itr_ != end_ && *itr_ == 0; ++itr_);
      index_ += (itr_ - old_itr);
			return *this;
    }
    /** Equality. */
    bool operator==(const const_set_index_iterator& rhs) const {
      return index_ == rhs.index_;
    }
    /** Inequality. */
    bool operator!=(const const_set_index_iterator& rhs) const {
      return index_ != rhs.index_;
    }

   private:
    /** Constructor. */
    const_set_index_iterator(const S* itr, const S* begin, const S* end) : end_(end) {
      for (itr_ = itr; itr_ != end_ && *itr_ == 0; ++itr_);
      index_ = itr_ - begin;
    }

    size_t index_;
    const S* itr_;
    const S* end_;
  };

  class bit_type {
    friend class BitString;

   public:
    /** Assignment operator. */
    bit_type& operator=(bool rhs) {
      if (rhs) {
        val_ |= mask_;
      } else {
        val_ &= ~mask_;
      }
      return *this;
    }
    /** Implicit conversion to bool. */
    operator bool() const {
      return val_ & mask_;
    }

   private:
    /** Constructor. */
    bit_type(uint64_t& val, uint64_t mask) : val_(val), mask_(mask) { }

    uint64_t& val_;
    uint64_t mask_;
  };

  typedef const_set_index_iterator<uint8_t> const_set_byte_index_iterator;
  typedef const_set_index_iterator<uint16_t> const_set_word_index_iterator;
  typedef const_set_index_iterator<uint32_t> const_set_double_index_iterator;
  typedef const_set_index_iterator<uint64_t> const_set_quad_index_iterator;

  typedef uint8_t* fixed_byte_iterator;
  typedef const uint8_t* const_fixed_byte_iterator;
  typedef uint16_t* fixed_word_iterator;
  typedef const uint16_t* const_fixed_word_iterator;
  typedef uint32_t* fixed_double_iterator;
  typedef const uint32_t* const_fixed_double_iterator;
  typedef uint64_t* fixed_quad_iterator;
  typedef const uint64_t* const_fixed_quad_iterator;
  typedef float* float_single_iterator;
  typedef const float* const_float_single_iterator;
  typedef double* float_double_iterator;
  typedef const double* const_float_double_iterator;

  /** Default constructor. */
  BitString() : contents_(), num_bits_(0) { }
  /** Copy constructor. */
  BitString(const BitString& rhs) {
    contents_ = rhs.contents_;
    num_bits_ = rhs.num_bits_;
  }
  /** Move constructor. */
  BitString(BitString&& rhs) {
    contents_ = std::move(rhs.contents_);
    num_bits_ = rhs.num_bits_;
  }
  /** Assignment operator. */
  BitString& operator=(const BitString& rhs) {
    BitString(rhs).swap(*this);
    return *this;
  }
  /** Move assignment operator. */
  BitString& operator=(const BitString && rhs) {
    BitString(std::move(rhs)).swap(*this);
    return *this;
  }

  /** Returns the number of bits in this string. */
  size_t num_bits() const {
    return num_bits_;
  }
  /** Returns the number of bytes in this string. */
  size_t num_fixed_bytes() const {
    return num_bits_ / 8;
  }
  /** Returns the number of words in this string. */
  size_t num_fixed_words() const {
    return num_bits_ / 16;
  }
  /** Returns the number of doubles in this string. */
  size_t num_fixed_doubles() const {
    return num_bits_ / 32;
  }
  /** Returns the number of quads in this string. */
  size_t num_fixed_quads() const {
    return num_bits_ / 64;
  }
  /** Returns the number of floats in this string. */
  size_t num_float_singles() const {
    return num_bits_ / 32;
  }
  /** Returns the number of doubles in this string. */
  size_t num_float_doubles() const {
    return num_bits_ / 64;
  }

	/** Returns the number of set bits in this string. */
	size_t num_set_bits() const {
		assert(false);
		return 0;
	}
	/** Returns the number of set bytes in this string. */
	size_t num_set_bytes() const {
		size_t count = 0;
		for ( auto i = fixed_byte_begin(), ie = fixed_byte_end(); i != ie; ++i ) {
			count += (*i > 0) ? 1 : 0;
		}
		return count;
	}
	/** Returns the number of set words in this string. */
	size_t num_set_words() const {
		size_t count = 0;
		for ( auto i = fixed_word_begin(), ie = fixed_word_end(); i != ie; ++i ) {
			count += (*i > 0) ? 1 : 0;
		}
		return count;
	}
	/** Returns the number of set doubles in this string. */
	size_t num_set_doubles() const {
		size_t count = 0;
		for ( auto i = fixed_double_begin(), ie = fixed_double_end(); i != ie; ++i ) {
			count += (*i > 0) ? 1 : 0;
		}
		return count;
	}
	/** Returns the number of set quads in this string. */
	size_t num_set_quads() const {
		size_t count = 0;
		for ( auto i = fixed_quad_begin(), ie = fixed_quad_end(); i != ie; ++i ) {
			count += (*i > 0) ? 1 : 0;
		}
		return count;
	}

  /** Returns a bit. */
  bit_type get_bit(size_t i) {
    assert(i < num_bits());
    return bit_type(contents_[i / 64], 0x1ull << (i % 64));
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
    return contents_[i / 64] & (0x1ull<< (i % 64));
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

  /** Set bit index iterator. */
  const_set_bit_index_iterator set_bit_index_begin() const {
    return const_set_bit_index_iterator(contents_.begin(), contents_.begin(), contents_.end(),
                                        num_bits());
  }
  /** Set bit index iterator. */
  const_set_bit_index_iterator set_bit_index_end() const {
    return const_set_bit_index_iterator(contents_.end(), contents_.begin(), contents_.end(),
                                        num_bits());
  }

  /** Set byte index iterator. */
  const_set_byte_index_iterator set_byte_index_begin() const {
    return const_set_byte_index_iterator(fixed_byte_begin(), fixed_byte_begin(), fixed_byte_end());
  }
  /** Set byte index iterator. */
  const_set_byte_index_iterator set_byte_index_end() const {
    return const_set_byte_index_iterator(fixed_byte_end(), fixed_byte_begin(), fixed_byte_end());
  }

  /** Set word index iterator. */
  const_set_word_index_iterator set_word_index_begin() const {
    return const_set_word_index_iterator(fixed_word_begin(), fixed_word_begin(), fixed_word_end());
  }
  /** Set word index iterator. */
  const_set_word_index_iterator set_word_index_end() const {
    return const_set_word_index_iterator(fixed_word_end(), fixed_word_begin(), fixed_word_end());
  }

  /** Set double index iterator. */
  const_set_double_index_iterator set_double_index_begin() const {
    return const_set_double_index_iterator(fixed_double_begin(), fixed_double_begin(),
                                           fixed_double_end());
  }
  /** Set double index iterator. */
  const_set_double_index_iterator set_double_index_end() const {
    return const_set_double_index_iterator(fixed_double_end(), fixed_double_begin(),
                                           fixed_double_end());
  }

  /** Set quad index iterator. */
  const_set_quad_index_iterator set_quad_index_begin() const {
    return const_set_quad_index_iterator(fixed_quad_begin(), fixed_quad_begin(), fixed_quad_end());
  }
  /** Set quad index iterator. */
  const_set_quad_index_iterator set_quad_index_end() const {
    return const_set_quad_index_iterator(fixed_quad_end(), fixed_quad_begin(), fixed_quad_end());
  }

  /** Byte iterator. */
  fixed_byte_iterator fixed_byte_begin() {
    return (uint8_t*) contents_.data();
  }
  /** Byte iterator. */
  fixed_byte_iterator fixed_byte_end() {
    return (uint8_t*) contents_.data() + num_fixed_bytes();
  }
  /** Byte iterator. */
  const_fixed_byte_iterator fixed_byte_begin() const {
    return (uint8_t*) contents_.data();
  }
  /** Byte iterator. */
  const_fixed_byte_iterator fixed_byte_end() const {
    return (uint8_t*) contents_.data() + num_fixed_bytes();
  }

  /** Word iterator. */
  fixed_word_iterator fixed_word_begin() {
    return (uint16_t*) contents_.data();
  }
  /** Word iterator. */
  fixed_word_iterator fixed_word_end() {
    return (uint16_t*) contents_.data() + num_fixed_words();
  }
  /** Word iterator. */
  const_fixed_word_iterator fixed_word_begin() const {
    return (uint16_t*) contents_.data();
  }
  /** Word iterator. */
  const_fixed_word_iterator fixed_word_end() const {
    return (uint16_t*) contents_.data() + num_fixed_words();
  }

  /** Double iterator. */
  fixed_double_iterator fixed_double_begin() {
    return (uint32_t*) contents_.data();
  }
  /** Double iterator. */
  fixed_double_iterator fixed_double_end() {
    return (uint32_t*) contents_.data() + num_fixed_doubles();
  }
  /** Double iterator. */
  const_fixed_double_iterator fixed_double_begin() const {
    return (uint32_t*) contents_.data();
  }
  /** Double iterator. */
  const_fixed_double_iterator fixed_double_end() const {
    return (uint32_t*) contents_.data() + num_fixed_doubles();
  }

  /** Quad iterator. */
  fixed_quad_iterator fixed_quad_begin() {
    return (uint64_t*) contents_.data();
  }
  /** Quad iterator. */
  fixed_quad_iterator fixed_quad_end() {
    return (uint64_t*) contents_.data() + num_fixed_quads();
  }
  /** Quad iterator. */
  const_fixed_quad_iterator fixed_quad_begin() const {
    return (uint64_t*) contents_.data();
  }
  /** Quad iterator. */
  const_fixed_quad_iterator fixed_quad_end() const {
    return (uint64_t*) contents_.data() + num_fixed_quads();
  }

  /** Float iterator. */
  float_single_iterator float_single_begin() {
    return (float*) contents_.data();
  }
  /** Float iterator. */
  float_single_iterator float_single_end() {
    return (float*) contents_.data() + num_float_singles();
  }
  /** Float iterator. */
  const_float_single_iterator float_single_begin() const {
    return (float*) contents_.data();
  }
  /** Float iterator. */
  const_float_single_iterator float_single_end() const {
    return (float*) contents_.data() + num_float_singles();
  }

  /** Double iterator. */
  float_double_iterator float_double_begin() {
    return (double*) contents_.data();
  }
  /** Double iterator. */
  float_double_iterator float_double_end() {
    return (double*) contents_.data() + num_float_doubles();
  }
  /** Double iterator. */
  const_float_double_iterator float_double_begin() const {
    return (double*) contents_.data();
  }
  /** Double iterator. */
  const_float_double_iterator float_double_end() const {
    return (double*) contents_.data() + num_float_doubles();
  }

  /** Bit-wise and. */
  BitString& operator&=(const BitString& rhs) {
    auto i = 0;

#if defined(__AVX2__) && defined(__AVX__)
    for (; i + 4 <= contents_.size(); i += 4) {
      auto x = _mm256_load_si256((__m256i*) &contents_[i]);
      auto y = _mm256_load_si256((__m256i*) &rhs.contents_[i]);
      x = _mm256_and_si256(x, y);
      _mm256_store_si256((__m256i*)&contents_[i], x);
    }
#elif defined(__AVX__)
    for (; i + 2 <= contents_.size(); i += 2) {
      auto x = _mm_load_si128((__m128i*) &contents_[i]);
      auto y = _mm_load_si128((__m128i*) &rhs.contents_[i]);
      x = _mm_and_si128(x, y);
      _mm_store_si128((__m128i*)&contents_[i], x);
    }
#endif
    for (; i < contents_.size(); ++i) {
      contents_[i] &= rhs.contents_[i];
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
    for (; i + 4 <= contents_.size() ; i += 4) {
      auto x = _mm256_load_si256((__m256i*) &contents_[i]);
      auto y = _mm256_load_si256((__m256i*) &rhs.contents_[i]);
      x = _mm256_or_si256(x, y);
      _mm256_store_si256((__m256i*)&contents_[i], x);
    }
#elif defined(__AVX__)
    for (; i + 2 <= contents_.size() ; i += 2) {
      auto x = _mm_load_si128((__m128i*) &contents_[i]);
      auto y = _mm_load_si128((__m128i*) &rhs.contents_[i]);
      x = _mm_or_si128(x, y);
      _mm_store_si128((__m128i*)&contents_[i], x);
    }
#endif
    for (; i < contents_.size(); ++i) {
      contents_[i] |= rhs.contents_[i];
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
    for (; i + 4 <= contents_.size() ; i += 4) {
      auto x = _mm256_load_si256((__m256i*) &contents_[i]);
      auto y = _mm256_load_si256((__m256i*) &rhs.contents_[i]);
      x = _mm256_xor_si256(x, y);
      _mm256_store_si256((__m256i*)&contents_[i], x);
    }
#elif defined(__AVX__)
    for (; i + 2 <= contents_.size() ; i += 2) {
      auto x = _mm_load_si128((__m128i*) &contents_[i]);
      auto y = _mm_load_si128((__m128i*) &rhs.contents_[i]);
      x = _mm_xor_si128(x, y);
      _mm_store_si128((__m128i*)&contents_[i], x);
    }
#endif
    for (; i < contents_.size(); ++i) {
      contents_[i] ^= rhs.contents_[i];
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
    // Any good ideas for how to vectorize this effectively?

    auto ret = *this;
    for (size_t i = 0; i < contents_.size(); ++i) {
      ret.contents_[i] = ~contents_[i];
    }
    return ret;
  }

  /** Underlying data. */
  void* data() {
    return contents_.data();
  }

  /** Subscript operator. */
  bit_type operator[](size_t i) {
    return get_bit(i);
  }
  /** Subscript operator. */
  bool operator[](size_t i) const {
    return get_bit(i);
  }

  /** Equality. */
  bool operator==(const BitString& rhs) const {
    return contents_ == rhs.contents_ && num_bits_ == rhs.num_bits_;
  }
  /** Inequality. */
  bool operator!=(const BitString& rhs) const {
    return contents_ != rhs.contents_ || num_bits_ != rhs.num_bits_;
  }

  /** STL-compliant swap. */
  void swap(BitString& rhs) {
    std::swap(contents_, rhs.contents_);
    std::swap(num_bits_, rhs.num_bits_);
  }

 protected:
  alignas(32) T contents_;
  size_t num_bits_;
};

} // namespace cpputil

namespace std {

/** STL-compliant swap. */
template <typename T>
void swap(cpputil::BitString<T>& lhs, cpputil::BitString<T>& rhs) {
  lhs.swap(rhs);
}

} // namespace

#endif

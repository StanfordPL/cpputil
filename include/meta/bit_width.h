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

#ifndef CPPUTIL_INCLUDE_META_BIT_WIDTH_H
#define CPPUTIL_INCLUDE_META_BIT_WIDTH_H

#include <stdint.h>
#include <type_traits>

namespace cpputil {

template <typename T>
struct bit_width : public std::integral_constant < int, -1 > { };

template <>
struct bit_width<char> : public std::integral_constant<int, 8> { };

template <>
struct bit_width<const char> : public std::integral_constant<int, 8> { };

template <>
struct bit_width<char16_t> : public std::integral_constant<int, 16> { };

template <>
struct bit_width<const char16_t> : public std::integral_constant<int, 16> { };

template <>
struct bit_width<char32_t> : public std::integral_constant<int, 32> { };

template <>
struct bit_width<const char32_t> : public std::integral_constant<int, 32> { };

template <>
struct bit_width<int8_t> : public std::integral_constant<int, 8> { };

template <>
struct bit_width<const int8_t> : public std::integral_constant<int, 8> { };

template <>
struct bit_width<uint8_t> : public std::integral_constant<int, 8> { };

template <>
struct bit_width<const uint8_t> : public std::integral_constant<int, 8> { };

template <>
struct bit_width<int16_t> : public std::integral_constant<int, 16> { };

template <>
struct bit_width<const int16_t> : public std::integral_constant<int, 16> { };

template <>
struct bit_width<uint16_t> : public std::integral_constant<int, 16> { };

template <>
struct bit_width<const uint16_t> : public std::integral_constant<int, 16> { };

template <>
struct bit_width<int32_t> : public std::integral_constant<int, 32> { };

template <>
struct bit_width<const int32_t> : public std::integral_constant<int, 32> { };

template <>
struct bit_width<uint32_t> : public std::integral_constant<int, 32> { };

template <>
struct bit_width<const uint32_t> : public std::integral_constant<int, 32> { };

template <>
struct bit_width<float> : public std::integral_constant<int, 32> { };

template <>
struct bit_width<const float> : public std::integral_constant<int, 32> { };

template <>
struct bit_width<int64_t> : public std::integral_constant<int, 64> { };

template <>
struct bit_width<const int64_t> : public std::integral_constant<int, 64> { };

template <>
struct bit_width<uint64_t> : public std::integral_constant<int, 64> { };

template <>
struct bit_width<const uint64_t> : public std::integral_constant<int, 64> { };

template <>
struct bit_width<double> : public std::integral_constant<int, 64> { };

template <>
struct bit_width<const double> : public std::integral_constant<int, 64> { };

} // namespace cpputil

#endif





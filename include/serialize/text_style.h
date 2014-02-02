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

#ifndef CPPUTIL_INCLUDE_SERIALIZE_TEXT_STYLE_H
#define CPPUTIL_INCLUDE_SERIALIZE_TEXT_STYLE_H

namespace cpputil {

template <char Dec = true, size_t HexGroup = 8,
          char Open = '{', char Close = '}', char Quote = '"', char Etc = '.'>
struct TextStyle {
  static constexpr bool dec() {
    return Dec;
  }

  static constexpr size_t hex_group() {
    return HexGroup;
  }

  static constexpr char open() {
    return Open;
  }

  static constexpr char close() {
    return Close;
  }

  static constexpr char quote() {
    return Quote;
  }

  static constexpr char etc() {
    return Etc;
  }
};

} // namespace cpputil

#endif


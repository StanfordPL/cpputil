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

#ifndef CPPUTIL_INCLUDE_IO_MULTISTREAM_H
#define CPPUTIL_INCLUDE_IO_MULTISTREAM_H

#include <iostream>
#include <streambuf>

#include "include/io/multibuf.h"

namespace cpputil {

template <typename Ch, typename Tr>
class basic_omultistream : public std::basic_ostream<Ch, Tr> {
 public:
  explicit basic_omultistream()
    : std::basic_ostream<Ch, Tr>(&buf_), buf_() { }

  explicit basic_omultistream(std::basic_ostream<Ch, Tr>& os)
    : std::basic_ostream<Ch, Tr>(&buf_), buf_(os.rdbuf()) { }

  explicit basic_omultistream(std::basic_streambuf<Ch, Tr>& sb)
    : std::basic_ostream<Ch, Tr>(&buf_), buf_(sb) { }

  virtual ~basic_omultistream() { }

  void insert(std::basic_ostream<Ch, Tr>& os) {
    buf_.insert(os.rdbuf());
  }

  void clear() {
    buf_.clear();
  }

 private:
  basic_multibuf<Ch, Tr> buf_;
};

typedef basic_omultistream<char, std::char_traits<char>> omultistream;
typedef basic_omultistream<wchar_t, std::char_traits<wchar_t>> womultistream;

} // namespace cpputil

#endif

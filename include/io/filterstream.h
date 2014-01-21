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

#ifndef CPPUTIL_INCLUDE_IO_FILTER_STREAM_H
#define CPPUTIL_INCLUDE_IO_FILTER_STREAM_H

#include <iostream>
#include <streambuf>
#include <vector>

#include "include/io/filterbuf.h"

namespace cpputil {

template <typename F, typename Ch, typename Tr>
class basic_ifilterstream : public std::basic_istream<Ch, Tr> {
 public:
  explicit basic_ifilterstream(std::basic_istream<Ch, Tr>& is)
    : std::basic_istream<Ch, Tr>(&buf_), buf_(is.rdbuf()) { }

  explicit basic_ifilterstream(std::basic_streambuf<Ch, Tr>& sb)
    : std::basic_istream<Ch, Tr>(&buf_), buf_(sb) { }

  virtual ~basic_ifilterstream() { }

  F& filter() {
    return buf_.filter();
  }

  void reserve(size_t bytes) {
    buf_.reserve(bytes);
  }

 private:
  basic_ifilterbuf<F, Ch, Tr> buf_;
};

template <typename F>
using ifilterstream = basic_ifilterstream<F, char, std::char_traits<char>>;
template <typename F>
using wifilterstream = basic_ifilterstream<F, wchar_t, std::char_traits<wchar_t>>;

template <typename F, typename Ch, typename Tr>
class basic_ofilterstream : public std::basic_ostream<Ch, Tr> {
 public:
  explicit basic_ofilterstream(std::basic_ostream<Ch, Tr>& os)
    : std::basic_ostream<Ch, Tr>(&buf_), buf_(os.rdbuf()) { }

  explicit basic_ofilterstream(std::basic_streambuf<Ch, Tr>& sb)
    : std::basic_ostream<Ch, Tr>(&buf_), buf_(sb) { }

  virtual ~basic_ofilterstream() { }

  F& filter() {
    return buf_.filter();
  }

 private:
  basic_ofilterbuf<F, Ch, Tr> buf_;
};

template <typename F>
using ofilterstream = basic_ofilterstream<F, char, std::char_traits<char>>;
template <typename F>
using wofilterstream = basic_ofilterstream<F, wchar_t, std::char_traits<wchar_t>>;

} // namespace cpputil

#endif


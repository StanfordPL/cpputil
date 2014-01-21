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

#ifndef CPPUTIL_INCLUDE_IO_REDIRECTSTREAM_H
#define CPPUTIL_INCLUDE_IO_REDIRECTSTREAM_H

#include <iostream>
#include <streambuf>

#include "include/io/redirectbuf.h"

namespace cpputil {

template <typename Ch, typename Tr>
class basic_iredirectstream : public std::basic_istream<Ch, Tr> {
 public:
  explicit basic_iredirectstream(std::basic_istream<Ch, Tr>& is)
    : std::basic_istream<Ch, Tr>(&buf_), buf_(is.rdbuf()) { }

  explicit basic_iredirectstream(std::basic_streambuf<Ch, Tr>* sb)
    : std::basic_istream<Ch, Tr>(&buf_), buf_(sb) { }

  virtual ~basic_iredirectstream() { }

 private:
  basic_redirectbuf<Ch, Tr> buf_;
};

typedef basic_iredirectstream<char, std::char_traits<char>> iredirectstream;
typedef basic_iredirectstream<wchar_t, std::char_traits<wchar_t>> wiredirectstream;

template <typename Ch, typename Tr>
class basic_oredirectstream : public std::basic_ostream<Ch, Tr> {
 public:
  explicit basic_oredirectstream(std::basic_ostream<Ch, Tr>& os)
    : std::basic_ostream<Ch, Tr>(&buf_), buf_(os.rdbuf()) { }

  explicit basic_oredirectstream(std::basic_streambuf<Ch, Tr>* sb)
    : std::basic_ostream<Ch, Tr>(&buf_), buf_(sb) { }

  virtual ~basic_oredirectstream() { }

 private:
  basic_redirectbuf<Ch, Tr> buf_;
};

typedef basic_oredirectstream<char, std::char_traits<char>> oredirectstream;
typedef basic_oredirectstream<wchar_t, std::char_traits<wchar_t>> woredirectstream;

template <typename Ch, typename Tr>
class basic_redirectstream : public std::basic_iostream<Ch, Tr> {
 public:
  explicit basic_redirectstream(std::basic_iostream<Ch, Tr>& ios)
    : std::basic_iostream<Ch, Tr>(&buf_), buf_(ios.rdbuf()) { }

  explicit basic_redirectstream(std::basic_streambuf<Ch, Tr>* sb)
    : std::basic_iostream<Ch, Tr>(&buf_), buf_(sb) { }

  virtual ~basic_redirectstream() { }

 private:
  basic_redirectbuf<Ch, Tr> buf_;
};

typedef basic_redirectstream<char, std::char_traits<char>> redirectstream;
typedef basic_redirectstream<wchar_t, std::char_traits<wchar_t>> wredirectstream;

} // namespace cpputil

#endif

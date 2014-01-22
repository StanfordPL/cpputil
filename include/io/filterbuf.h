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

#ifndef CPPUTIL_INCLUDE_IO_FILTERBUF_H
#define CPPUTIL_INCLUDE_IO_FILTERBUF_H

#include <iostream>
#include <streambuf>
#include <vector>

namespace cpputil {

template <typename F, typename Ch, typename Tr>
class basic_ifilterbuf : public std::basic_streambuf<Ch, Tr> {
 public:
  typedef typename std::basic_streambuf<Ch, Tr>::char_type char_type;
  typedef typename std::basic_streambuf<Ch, Tr>::int_type int_type;
  typedef typename std::basic_streambuf<Ch, Tr>::off_type off_type;
  typedef typename std::basic_streambuf<Ch, Tr>::pos_type pos_type;
  typedef typename std::basic_streambuf<Ch, Tr>::traits_type traits_type;

  basic_ifilterbuf(std::basic_streambuf<Ch, Tr>* buf)
    : buf_(buf), next_(16) { }

  virtual ~basic_ifilterbuf() { }

  F& filter() {
    return filter_;
  }

  void reserve(size_t bytes) {
    next_.reserve(bytes);
  }

 protected:
  virtual int_type underflow() {
    if (std::basic_streambuf<Ch, Tr>::gptr() == std::basic_streambuf<Ch, Tr>::egptr()) {
      size_t count = 0;
      do {
        const auto c = buf_->sbumpc();
        count = filter_(c, next_.data());
      } while (count == 0);
      std::basic_streambuf<Ch, Tr>::setg(next_.data(), next_.data(), next_.data() + count);
    }
    return *std::basic_streambuf<Ch, Tr>::gptr();
  }

  virtual int_type sync() {
    return buf_->pubsync();
  }

 private:
  std::basic_streambuf<Ch, Tr>* buf_;
  std::vector<Ch> next_;
  F filter_;
};

template <typename F, typename Ch, typename Tr>
class basic_ofilterbuf : public std::basic_streambuf<Ch, Tr> {
 public:
  basic_ofilterbuf(std::basic_streambuf<Ch, Tr>* buf)
    : buf_(buf) { }

  virtual ~basic_ofilterbuf() { }

  F& filter() {
    return filter_;
  }

 protected:
  virtual int sync() {
    return buf_->pubsync();
  }

  virtual int overflow(int c = EOF) {
    if (c == EOF) {
      return EOF;
    }

    filter_(buf_, c);
    return 1;
  }

 private:
  std::basic_streambuf<Ch, Tr>* buf_;
  F filter_;
};


} // namespace cpputil

#endif


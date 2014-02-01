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

#ifndef CPPUTIL_INCLUDE_IO_MULTIBUF_H
#define CPPUTIL_INCLUDE_IO_MULTIBUF_H

#include <iostream>
#include <streambuf>
#include <unordered_set>

namespace cpputil {

template <typename Ch, typename Tr>
class basic_multibuf : public std::basic_streambuf<Ch, Tr> {
 public:
  typedef typename std::basic_streambuf<Ch, Tr>::char_type char_type;
  typedef typename std::basic_streambuf<Ch, Tr>::int_type int_type;
  typedef typename std::basic_streambuf<Ch, Tr>::off_type off_type;
  typedef typename std::basic_streambuf<Ch, Tr>::pos_type pos_type;
  typedef typename std::basic_streambuf<Ch, Tr>::traits_type traits_type;

  explicit basic_multibuf() { }

  explicit basic_multibuf(std::basic_streambuf<Ch, Tr>* buf) {
    insert(buf);
  }

  virtual ~basic_multibuf() { }

  void insert(std::basic_streambuf<Ch, Tr>* buf) {
    bufs_.insert(buf);
  }

  void clear() {
    bufs_.clear();
  }

 protected:
  virtual int_type sync() {
    for (auto buf : bufs_)
      if (buf->pubsync() != 0) {
        return -1;
      }

    return 0;
  }

  virtual int_type overflow(int_type c = traits_type::eof()) {
    const auto ch = traits_type::to_char_type(c);
    for (auto buf : bufs_)
      if (traits_type::eq_int_type(buf->sputc(ch), traits_type::eof())) {
        return traits_type::eof();
      }

    return c;
  }

 private:
  std::unordered_set<std::basic_streambuf<Ch, Tr>*> bufs_;
};

typedef basic_multibuf<char, std::char_traits<char>> multibuf;
typedef basic_multibuf<wchar_t, std::char_traits<wchar_t>> wmultibuf;

} // namespace cpputil

#endif

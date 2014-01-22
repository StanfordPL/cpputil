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

#ifndef CPPUTIL_INCLUDE_IO_INDENT_H
#define CPPUTIL_INCLUDE_IO_INDENT_H

#include <streambuf>

namespace cpputil {

class Indent {
 public:
  Indent() :
    indent_(0), width_(2), pending_(true) { }

  Indent& indent(size_t count = 1) {
    indent_ += count;
    return *this;
  }

  Indent& unindent(size_t count = 1) {
    if (count > indent_) {
      indent_ = 0;
    } else {
      indent_ -= count;
    }
    return *this;
  }

  Indent& width(size_t width) {
    width_ = width;
    return *this;
  }

  void operator()(std::streambuf* sb, char c) {
    if (pending_) {
      for (size_t i = 0, ie = indent_ * width_; i < ie; ++i) {
        sb->sputc(' ');
      }
      pending_ = false;
    }

    sb->sputc(c);
    if (c == '\n' || c == '\r') {
      pending_ = true;
    }
  }

 private:
  size_t indent_;
  size_t width_;
  bool pending_;
};

} // namespace cpputil

#endif

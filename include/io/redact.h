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

#ifndef CPPUTIL_INCLUDE_IO_REDACT_H
#define CPPUTIL_INCLUDE_IO_REDACT_H

#include <iomanip>
#include <streambuf>

namespace cpputil {

class Redact {
 public:
  Redact() :
    on_(false) { }

  Redact& on() {
    on_ = true;
    return *this;
  }

  Redact& off() {
    on_ = false;
    return *this;
  }

  void operator()(std::streambuf* sb, char c) {
    sb->sputc(on_ && isgraph(c) ? 'x' : c);
  }

 private:
  bool on_;
};

} // namespace cpputil

#endif

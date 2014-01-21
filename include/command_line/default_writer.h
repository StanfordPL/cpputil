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

#ifndef CPPUTIL_INCLUDE_COMMAND_LINE_DEFAULT_WRITER_H
#define CPPUTIL_INCLUDE_COMMAND_LINE_DEFAULT_WRITER_H

#include <iostream>

namespace cpputil {

template <typename T>
class DefaultWriter {
 public:
  /** Uses a type's ostream overload */
  void operator()(std::ostream& os, const T& t) {
    os << t;
  }
};

} // namespace cpputil

#endif


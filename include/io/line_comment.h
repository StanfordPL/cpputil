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

#ifndef CPPUTIL_INCLUDE_IO_LINE_COMMENT_H
#define CPPUTIL_INCLUDE_IO_LINE_COMMENT_H

namespace cpputil {

template <char C>
class LineComment {
 public:
  LineComment() :
    ignoring_(false) { }

  size_t operator()(char c, char* buffer) {
    switch (c) {
      case C:
        ignoring_ = true;
        return 0;

      case '\n':
        ignoring_ = false;
        buffer[0] = c;
        return 1;

      default:
        if (!ignoring_ || c == EOF) {
          buffer[0] = c;
          return 1;
        } else {
          return 0;
        }
    }
  }

 private:
  bool ignoring_;
};

} // namespace cpputil

#endif

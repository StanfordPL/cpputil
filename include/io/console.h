// Copyright 2015 eric schkufza
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

#ifndef CPPUTIL_INCLUDE_IO_CONSOLE_H
#define CPPUTIL_INCLUDE_IO_CONSOLE_H

#include <iostream>

#include "include/io/abort.h"
#include "include/io/filterstream.h"
#include "include/io/prefix.h"

namespace cpputil {

class Console {
public:
  typedef ofilterstream<Prefix> message_type;
  typedef ofilterstream<Abort> error_type;

  /** Messages are routed through cout. */
  static message_type& msg() {
    static message_type m(std::cout);
    return m;
  }
  /** Warnings are assigned a prefix and routed through cerr. */
  static message_type& warn() {
    static message_type w(std::cerr);
    w.filter().prefix("WARNING: ");
    return w;
  }
  /** Errors are assigned a prefix, routed through cerr, and invoke shutdown. */
  static error_type& error(int code = 1) {
    static message_type m(std::cerr);
    m.filter().prefix("FATAL ERROR: ");

    static error_type e(m);
    e.filter().code(code);

    return e;
  }
};

} // namespace cpputil

#endif

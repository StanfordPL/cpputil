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

#ifndef CPPUTIL_INCLUDE_COMMAND_LINE_FLAG_ARG_H
#define CPPUTIL_INCLUDE_COMMAND_LINE_FLAG_ARG_H

#include <string>

#include "include/command_line/arg.h"

namespace cpputil {

class FlagArg : public Arg {
 public:
  virtual ~FlagArg() = default;

  /** Creates and registers a new flag */
  static FlagArg& create(const std::string& opt) {
    return *(new FlagArg(opt));
  }

  /** FlagArgs don't consume anything */
  virtual std::pair<size_t, size_t> read(int argc, char** argv) {
    val_ = !get_appearances(argc, argv).empty();
    return std::make_pair(0, 0);
  }

  /** Create a new arg alias (dashes implicit; chars get 1, strings 2) */
  FlagArg& alternate(const std::string& a) {
    Arg::alternate(a);
    return *this;
  }

  /** Reset arg usage */
  FlagArg& usage(const std::string& u) {
    Arg::usage(u);
    return *this;
  }

  /** Reset arg description */
  FlagArg& description(const std::string& d) {
    Arg::description(d);
    return *this;
  }

  /** Implicit conversion to bool */
  operator bool& () {
    return val_;
  }

  /** Explicit conversion to bool */
  bool& value() {
    return val_;
  }

  /** Prints true or false */
  virtual void debug(std::ostream& os) const {
    os << (val_ ? "true" : "false");
  }

 private:
  /** Did this arg appear on the command line? */
  bool val_;

  /** Flag args are false by default */
  FlagArg(const std::string& opt) : Arg {opt}, val_ {false} { }
};

} // namespace cpputil

#endif


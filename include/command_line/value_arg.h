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

#ifndef CPPUTIL_INCLUDE_COMMAND_LINE_VALUE_ARG_H
#define CPPUTIL_INCLUDE_COMMAND_LINE_VALUE_ARG_H

#include <string>

#include "include/command_line/arg.h"
#include "include/io/fail.h"
#include "include/serialize/text_reader.h"
#include "include/serialize/text_writer.h"

namespace cpputil {

template <typename T, typename R = TextReader<T>, typename W = TextWriter<T>>
class ValueArg : public Arg {
 public:
  virtual ~ValueArg() = default;

  /** Creates and registers a new flag */
  static ValueArg& create(const std::string& opt) {
    return *(new ValueArg(opt));
  }

  /** Consumes indices from first alias to next - */
  virtual std::pair<size_t, size_t> read(int argc, char** argv) {
    for (const int i : get_appearances(argc, argv)) {
      if (i == (argc - 1) || argv[i + 1][0] == '-') {
        error(parse_error_ + " No argument provided!");
        return std::make_pair(i, i);
      }

      std::istringstream iss(argv[i + 1]);
      T temp = T();
      R()(iss, temp);

      if (failed(iss)) {
				const auto msg = fail_msg(iss);
				if (msg == "") {
					error(parse_error_ + " No reason given!");
				} else {
					error(parse_error_ + " " + msg);
				}
      } else {
        val_ = temp;
      }
      set_provided();
      return std::make_pair(i, i + 1);
    }

    return std::make_pair(0, 0);
  }

  /** Create a new arg alias (hashes implicit; chars get 1, strings 2) */
  ValueArg& alternate(const std::string& a) {
    Arg::alternate(a);
    return *this;
  }

  /** Reset arg usage */
  ValueArg& usage(const std::string& u) {
    Arg::usage(u);
    return *this;
  }

  /** Reset arg description */
  ValueArg& description(const std::string& d) {
    Arg::description(d);
    return *this;
  }

  /** Resets arg default value */
  ValueArg& default_val(const T& t) {
    set_has_default();
    val_ = t;
    return *this;
  }

  /** Resets the parse error message */
  ValueArg& parse_error(const std::string& pe) {
    parse_error_ = pe;
    return *this;
  }

  /** Resets the required value. */
  ValueArg& required(const bool val = true) {
    Arg::required(val);
    return *this;
  }

  /** Implicit conversion to underlying type */
  operator T& () {
    return val_;
  }

  /** Explicit conversion to underlying type */
  T& value() {
    return val_;
  }

  /** Prints underlying value using writer */
  virtual void debug(std::ostream& os) const {
    W()(os, val_);
  }

 private:
  /** Underlying value, optionally specified on command line */
  T val_;
  /** String to emit if an error occurs during read() */
  std::string parse_error_;

  /** ValueArgs are assigned default constructor values by default */
  ValueArg(const std::string& opt) :
    Arg {opt} {
    usage("<value>");
    parse_error("Unable to parse value:");
  }
};

} // namespace cpputil

#endif


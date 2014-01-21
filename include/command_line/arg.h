#ifndef CPPUTIL_INCLUDE_COMMAND_LINE_ARG_H
#define CPPUTIL_INCLUDE_COMMAND_LINE_ARG_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <vector>

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

#include "include/command_line/arg_list.h"
#include "include/patterns/singleton.h"

namespace cpputil {

class Arg {
 public:
  virtual ~Arg() = default;

  /** Read an arg, returns range of indices consumed or (0,0) for none */
  virtual std::pair<size_t, size_t> read(int argc, char** argv) = 0;

  /** Returns true if an arg was not provided or read() without error */
  bool good() const {
    return error_ == "";
  }

  /** Alias iterator */
  typedef std::set<std::string>::const_iterator alias_iterator;

  /** First alias */
  alias_iterator alias_begin() const {
    return opts_.begin();
  }

  /** Last alias */
  alias_iterator alias_end() const {
    return opts_.end();
  }

  /** Appearance index iterator */
  typedef std::vector<size_t>::const_iterator appearance_iterator;

  /** First appearance in argv */
  appearance_iterator appearance_begin() const {
    return appearances_.begin();
  }

  /** Last appearance in argv */
  appearance_iterator appearance_end() const {
    return appearances_.end();
  }

  /** Does this arg appear more than once? */
  bool duplicated() const {
    return appearances_.size() > 1;
  }

  /** Prints arg usage */
  void usage(std::ostream& os) const {
    os << usage_;
  }

  /** Prints arg description */
  void description(std::ostream& os) const {
    os << description_;
  }

  /** Prints the cause of an error; valid iff good() == false */
  void error(std::ostream& os) const {
    os << error_;
  }

  /** Prints the value of an arg */
  virtual void debug(std::ostream& os) const = 0;

 protected:
  /** An arg must be assigned at least one alias */
  Arg(const std::string& opt) {
    alternate(opt);
    usage("");
    description("(no description provided)");
    survivable_error("");

    auto& arg_list = Singleton<ArgList>::get().args_;
    arg_list.push_back(this);
  }

  /** Create a new arg alias (dashes implicit; chars get 1, strings 2) */
  Arg& alternate(const std::string& a) {
    std::string alt = "";

    if (a.length() == 0) {
      fatal_error("Unable to register an arg named \"\"!");
    } else if (a.length() == 1) {
      if (a[0] == '-') {
        fatal_error("Unable to register an arg named \"-\"!");
      } else {
        alt = std::string("-") + a;
      }
    } else if (a.length() == 2 && a == "--") {
      fatal_error("Unable to register an arg named \"--\"!");
    } else {
      alt = std::string("--") + a;
    }

    const auto& arg_list = Singleton<ArgList>::get().args_;
    for (const auto arg : arg_list) {
      if (opts_.find(alt) != opts_.end()) {
        std::ostringstream oss;
        oss << "Unable to register duplicate arg name \"" << alt << "\"!";
        fatal_error(oss.str());
      }
    }

    opts_.insert(alt);

		return *this;
  }

  /** Reset arg usage */
  void usage(const std::string& u) {
    usage_ = u;
  }

  /** Reset arg description */
  void description(const std::string& d) {
    description_ = d;
  }

  /** Record indices in argv where arg aliases occur */
  std::vector<size_t>& get_appearances(int argc, char** argv) {
    appearances_.clear();
    for (auto i = 1; i < argc; ++i) {
      for (const auto& o : opts_) {
        if (o == argv[i]) {
          appearances_.push_back(i);
        }
      }
    }

    return appearances_;
  }

  /** Places a value in error_ to indicate trouble of some kind */
  void survivable_error(const std::string& error) {
    error_ = error;
  }

  /** Forces immediate program termination with message. */
  void fatal_error(const std::string& error) const {
    std::cerr << "FATAL ARGS ERROR: " << error << std::endl;
    exit(1);
  }

 private:
  /** Aliases for this arg ,ie: "-h --help" */
  std::set<std::string> opts_;
  /** Indices of alias appearances in argv */
  std::vector<size_t> appearances_;

  /** Example usage text, ie: "<int>" */
  std::string usage_;
  /** What does this arg do, ie: "Annealing constant" */
  std::string description_;
  /** A non-empty value here indicates that a survivable error occurred */
  std::string error_;
};

} // namespace cpputil

#endif


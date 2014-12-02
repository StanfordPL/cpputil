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

#ifndef CPPUTIL_INCLUDE_COMMAND_LINE_ARG_H
#define CPPUTIL_INCLUDE_COMMAND_LINE_ARG_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <vector>

#include "include/command_line/arg_registry.h"
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

  /** Is this argument required? */
  bool is_required() const {
    return required_;
  }

  /** Has this argument been set (or does it have a default value)? */
  bool has_been_provided() const {
    return is_provided_;
  }

  /** Prints the value of an arg */
  virtual void debug(std::ostream& os) const = 0;

 protected:
  /** Creating a singleton of this class will ensure Args aren't leaked. */
  struct ArgCleanup {
    ~ArgCleanup() {
      for (auto a : Singleton<ArgRegistry>::get().args_) {
        delete a;
      }
    }
  };

  /** An arg must be assigned at least one alias */
  Arg(const std::string& opt) : is_provided_(false) {
    alternate(opt);
    usage("");
    description("(no description provided)");
    error("");
    required(false);

    auto& ar = Singleton<ArgRegistry>::get();
    ar.insert(this);
    Singleton<ArgCleanup>::get();
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

  /** Create a new arg alias (dashes implicit; chars get 1, strings 2) */
  Arg& alternate(const std::string& a) {
    std::string alt = "";

    assert(a.length() != 0 && "Cannot register arg with no name!");
    assert(a.length() != 1 || a != "-" && "Cannot register arg with no name!");
    assert(a.length() != 2 || a != "--" && "Cannot register arg with no name!");

    if (a.length() == 1) {
      alt = std::string("-") + a;
    } else {
      alt = std::string("--") + a;
    }

    auto& ar = Singleton<ArgRegistry>::get();
    for (auto i = ar.args_.begin(), ie = ar.args_.end(); i != ie; ++i) {
      if ((*i)->opts_.find(alt) != (*i)->opts_.end()) {
        assert(false && "Cannot register arg with pre-existing name!");
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

  /** Places a value in error_ to indicate trouble of some kind */
  void error(const std::string& error) {
    error_ = error;
  }

  /** Reset the required argument. */
  void required(const bool val = true) {
    required_ = val;
  }

  /** Indicate that this argument has been set now. */
  void set_provided() {
    is_provided_ = true;
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
  /** Is this argument mandatory? */
  bool required_;
  /** Has this argument been provided in some way? */
  bool is_provided_;
};

} // namespace cpputil

#endif


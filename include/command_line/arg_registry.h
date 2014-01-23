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

#ifndef CPPUTIL_INCLUDE_COMMAND_LINE_ARG_REGISTRY_H
#define CPPUTIL_INCLUDE_COMMAND_LINE_ARG_REGISTRY_H

#include <string>
#include <vector>

namespace cpputil {

class Arg;

class ArgRegistry {
 public:
  struct ArgGroup {
    std::string heading;
    std::vector<Arg*> args;

    typedef std::vector<Arg*>::iterator arg_iterator;

    arg_iterator arg_begin() {
      return args.begin();
    }

    arg_iterator arg_end() {
      return args.end();
    }
  };

  ArgRegistry() :
    groups_ {{"", std::vector<Arg*>()}} { }

  void insert_arg(Arg* arg) {
    groups_.back().args.push_back(arg);
    args_.push_back(arg);
  }

  void insert_group(const std::string& heading) {
    if (groups_.size() > 1 || groups_.back().heading != "") {
      groups_.resize(groups_.size() + 1);
    }
    groups_.back().heading = heading;
  }

  typedef std::vector<ArgGroup>::iterator group_iterator;

  group_iterator group_begin() {
    return groups_.begin();
  }

  group_iterator group_end() {
    return groups_.end();
  }

  typedef std::vector<Arg*>::iterator arg_iterator;

  arg_iterator arg_begin() {
    return args_.begin();
  }

  arg_iterator arg_end() {
    return args_.end();
  }

 private:
  std::vector<ArgGroup> groups_;
  std::vector<Arg*> args_;
};

} // namespace cpputil

#endif


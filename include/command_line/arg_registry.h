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

#include "include/command_line/arg_group.h"

namespace cpputil {

class Arg;
class Heading;

class ArgRegistry {
  friend class Arg;
  friend class Args;
  friend class Heading;

 private:
  typedef std::vector<ArgGroup>::const_iterator group_iterator;
  typedef std::vector<Arg*>::const_iterator arg_iterator;

  std::vector<Arg*> args_;
  std::vector<Heading*> headings_;
  std::vector<ArgGroup> groups_;

  void insert(Arg* arg) {
    groups_.back().args_.push_back(arg);
    args_.push_back(arg);
  }

  void insert(Heading* heading, const std::string& text) {
    headings_.push_back(heading);
    groups_.push_back(ArgGroup(text));
  }
};

} // namespace cpputil

#endif


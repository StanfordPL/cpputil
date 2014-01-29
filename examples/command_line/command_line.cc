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

#include <set>
#include <vector>

#include "include/command_line/command_line.h"
#include "include/serialize/range_reader.h"

using namespace cpputil;
using namespace std;

auto& heading = Heading::create("Program-specific arguments");

auto& i = ValueArg<int>::create("i")
          .alternate("int")
          .usage("<int>")
          .default_val(10);

auto& s = ValueArg<string>::create("s")
          .alternate("str")
          .usage("\"...\"")
          .default_val("Hello, world");

auto& v = ValueArg<vector<int>, RangeReader<vector<int>,1,10>>::create("v")
          .alternate("vector")
          .usage("{ 1 2 3 }")
          .default_val({1, 2});

auto& set = ValueArg<set<char>, RangeReader<set<char>,'a','z'>>::create("set")
            .usage("{ a b c }")
            .default_val({'a', 'b'});

int main(int argc, char** argv) {
  CommandLineConfig::strict_with_convenience(argc, argv);
  return 0;
}


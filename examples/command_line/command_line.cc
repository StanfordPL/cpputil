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
#include "include/serialize/hex_reader.h"
#include "include/serialize/hex_writer.h"
#include "include/serialize/range_reader.h"

using namespace cpputil;
using namespace std;

auto& heading = Heading::create("Program-specific arguments");

auto& i = ValueArg<int, RangeReader<int, Range<int, 1, 10>>>::create("i")
          .alternate("int")
          .usage("| 0 <= i <= 10")
          .default_val(5);

auto& h = ValueArg<uint64_t, HexReader<uint64_t, 4>, HexWriter<uint64_t, 4>>::create("j")
					.alternate("hex")
					.usage("0123 4567 89ab cdef")
					.default_val(0);

auto& s = ValueArg<string>::create("s")
          .alternate("str")
          .usage("\"...\"")
          .default_val("Hello, world");

auto& v = ValueArg<vector<int>, RangeReader<vector<int>, Range<int, 1, 10>>>::create("v")
          .alternate("vector")
          .usage("{ 1 2 3 }")
          .default_val({1, 2, 3});

auto& sc = ValueArg<set<char>, RangeReader<set<char>, Range<char, 'a', 'z'>>>::create("sc")
           .usage("{ a b c }")
           .default_val({'a', 'b', 'c'});

int main(int argc, char** argv) {
  CommandLineConfig::strict_with_convenience(argc, argv);
  return 0;
}


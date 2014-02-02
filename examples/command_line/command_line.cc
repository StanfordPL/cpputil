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
#include "include/serialize/span_reader.h"
#include "include/serialize/text_style.h"

using namespace cpputil;
using namespace std;

auto& heading = Heading::create("Program-specific arguments:");

auto& i = ValueArg<int, RangeReader<int, Range<int, 1, 10>>>::create("i")
  .alternate("int")
  .usage("<int>")
  .description("i | 1 <= i <= 10")
  .default_val(5);

auto& h = ValueArg<uint64_t, HexReader<uint64_t>, HexWriter<uint64_t>>::create("j")
  .alternate("hex")
  .usage("<hex>")
  .description("A 16 digit hex value, grouped 8 digits at a time. ie: 01234567 89abcdef")
  .default_val(0);

auto& s = ValueArg<string>::create("s")
  .alternate("str")
  .usage("\"...\"")
  .default_val("Hello, world");

auto& v = ValueArg<vector<int>, SpanReader<vector<int>, Range<int, 1, 10>>>::create("v")
  .alternate("vector")
  .usage("{ 1 2 3 }")
  .description("A sequence of integers, each between 1 and 10, inclusive")
  .default_val({1, 2, 3});

auto& sc = ValueArg<set<char>, SpanReader<set<char>, Range<char, 'a', 'z'>>>::create("sc")
  .usage("{ a b c }")
  .description("A set of characters, each between a and z, inclusive. May include ellipses as shorthand. ie: { a ... d }")
  .default_val({'a', 'b', 'c'});

auto& vh = FileArg<vector<int>,
      SpanReader<vector<int>, Range<int, 0, 32>, TextStyle<false>>,
      TextWriter<vector<int>, TextStyle<false>>>::create("vh")
  .usage("/path/to/file.dat")
  .description("A sequence of 8 digit hex values. May include ellipses as shorthand. ie:{ 00000000 00000001 ... }")
  .default_val({0, 1, 2});

int main(int argc, char** argv) {
  CommandLineConfig::strict_with_convenience(argc, argv);
  return 0;
}


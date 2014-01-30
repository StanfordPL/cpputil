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

#include <iostream>
#include <sstream>

#include "include/serialize/hex_reader.h"
#include "include/serialize/hex_writer.h"

using namespace cpputil;
using namespace std;

template <typename T>
void check(T t) {
  T t2;

  stringstream ss;
  HexWriter<T>()(ss, t);
  HexReader<T>()(ss, t2);

  HexWriter<T>()(cout, t);
  cout << endl;
  HexWriter<T>()(cout, t2);
  cout << endl;
}

int main() {
  char c = 0xab;
  char16_t c16 = 0xabcd;
  char32_t c32 = 0xabcdef01;
  uint64_t u64 = 0xabcdef0123456789;

  check(c);
  check(c16);
  check(c32);
  check(u64);

  return 0;
};

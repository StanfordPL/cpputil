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

#include "include/io/filterstream.h"

using namespace cpputil;
using namespace std;

struct Nop {
  void operator()(streambuf* sb, char c) {
    sb->sputc(c);
  }
};

template <char C>
struct Skip {
  void operator()(streambuf* sb, char c) {
    if (c != C) {
      sb->sputc(c);
    }
  }
};

template <char C>
struct Double {
  size_t operator()(char c, char* buffer) {
    auto count = c != C ? 1 : 2;
    for (size_t i = 0; i < count; ++i) {
      buffer[i] = c;
    }
    return count;
  }
};

int main() {
  ofilterstream<Nop> fs(cout);
  ofilterstream<Skip<'H'>> fs2(fs);
  ofilterstream<Skip<'l'>> fs3(fs2);
  fs3 << "Hello world!" << endl;

  stringstream ss;
  ss << "1 2 3";

  ifilterstream<Double<'2'>> fs4(ss);
  int x, y, z;
  fs4 >> x >> y >> z;
  cout << x << " " << y << " " << z << endl;

  return 0;
}

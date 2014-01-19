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

#include "include/io/filterstream.h"
#include "include/io/indent.h"

using namespace cpputil;
using namespace std;

int main() {
  ofilterstream<Indent> os(cout);
  os << "Hello, world!" << endl;
  os.filter().indent();
  os << "Hello, world!" << endl;
  os.filter().indent();
  os << "Hello, world!" << endl;

  for (size_t i = 0; i < 100; ++i) {
    os.filter().unindent();
  }

  os << "Hello, world!" << endl;

  return 0;
}

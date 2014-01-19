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
#include <string>

#include "include/io/filterstream.h"
#include "include/io/column.h"

using namespace cpputil;
using namespace std;

struct Double {
  string x;
  string y;
};

struct Triple {
  int x;
  int y;
  int z;
};

struct Sext {
  Triple t1;
  Triple t2;
};

ostream& operator<<(ostream& os, const Double& d) {
  os << d.x << endl;
  os << d.y;
  return os;
}

ostream& operator<<(ostream& os, const Triple& t) {
  os << t.x << endl;
  os << t.y << endl;
  os << t.z;
  return os;
}

ostream& operator<<(ostream& os, const Sext& s) {
  os << s.t1 << endl;
  os << s.t2;
  return os;
}

int main() {
  ofilterstream<Column> os(cout);
  os.filter().padding(3);

  Double d {"Hello", "World!!!"};
  Triple t {1, 2, 3};
  Sext s {{1, 2, 3}, {4, 5, 6}};

  os << "Col 1" << endl << d;
  os.filter().next();
  os << "Col 2" << endl << t;
  os.filter().next();
  os << "Col 3" << endl << s;
  os.filter().done();

  return 0;
}

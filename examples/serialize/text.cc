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
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

#include "include/meta/is_stl_container.h"
#include "include/serialize/stl_debug.h"
#include "include/serialize/text_reader.h"
#include "include/serialize/text_writer.h"

using namespace cpputil;
using namespace std;

struct C {
  int x;
  char c;
  double d;
  string s;
};

namespace cpputil {

template <typename Delim>
struct TextWriter<C, Delim> {
  void operator()(ostream& os, const C& c) {
    os << Delim::open();
    TextWriter<int, Delim>()(os, c.x);
    os << " ";
    TextWriter<char, Delim>()(os, c.c);
    os << " ";
    TextWriter<double, Delim>()(os, c.d);
    os << " ";
    TextWriter<string, Delim>()(os, c.s);
    os << Delim::close();
  }
};

template <typename Delim>
struct TextReader<C, Delim> {
  void operator()(istream& is, C& c) {
    is.get();
    TextReader<int, Delim>()(is, c.x);
    is.get();
    TextReader<char, Delim>()(is, c.c);
    is.get();
    TextReader<double, Delim>()(is, c.d);
    is.get();
    TextReader<string, Delim>()(is, c.s);
    is.get();
  }
};

} // namespace cpputil

int main() {
  C c {1, 'c', 2.0, "Hello"};

	typedef vector<int> VI;
  VI vi {1, 2};

	typedef vector<C> VC;
	VC vc {c};

	typedef list<VI> L;
  L l {vi, vi};

	typedef map<L, VC> M;
  M m {{l, vc}};

	typedef pair<M, short> P;
  P p1 {m, 3};

  stringstream ss;
	ss << p1;

  P p2;
	ss >> p2;

	cout << p1 << endl;
	cout << p2 << endl;

  return 0;
};

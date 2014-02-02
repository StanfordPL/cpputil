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
#include <tuple>
#include <utility>
#include <vector>
#include <map>

#include "include/debug/stl_print.h"

using namespace cpputil;
using namespace std;

int main() {
  auto p = make_pair(1, 2.0);
  cout << p << endl;

  vector<int> v { 1, 2, 3, 4, 5};
  cout << v << endl;

  map<int, char> m { {1, 'a'}, {2, 'b'} };
  cout << m << endl;

  auto t = make_tuple(1, 2.0, "three", p, v, m);
  cout << t << endl;

  return 0;
}

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
#include <map>

#include "include/container/maputil.h"

using namespace cpputil;
using namespace std;

int main() {
  CppUtilMap<map<int, char>> m;
  for (int i = 0; i < 5; ++i) {
    m[i] = 'a' + i;
  }

  cout << "Pair iteration: [ ";
  for (const auto& i : m) {
    cout << "(" << i.first << "," << i.second << ") ";
  }
  cout << "]" << endl;

  cout << "Key iteration: [ ";
  for (auto i = m.key_begin(), ie = m.key_end(); i != ie; ++i) {
    cout << *i << " ";
  }
  cout << "]" << endl;

  cout << "Value iteration: [ ";
  for (auto i = m.value_begin(), ie = m.value_end(); i != ie; ++i) {
    cout << *i << " ";
  }
  cout << "]" << endl;

  return 0;
}

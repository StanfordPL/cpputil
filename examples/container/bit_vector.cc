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

#include <iomanip>
#include <iostream>

#include "include/container/bit_vector.h"

using namespace cpputil;
using namespace std;

int main() {
  BitVector b1(63);
  BitVector b2(31);

  for (auto i = 0; i < 63; ++i) {
    b1[i] = 0xff;
  }

  for (auto x : b1) {
    cout << hex << setw(2) << setfill(' ') << (int) x << " ";
  }
  cout << endl;
  for (auto x : b2) {
    cout << hex << setw(2) << setfill(' ') << (int) x << " ";
  }
  cout << endl;

  b2 |= b1;

  for (auto x : b1) {
    cout << hex << setw(2) << setfill(' ') << (int) x << " ";
  }
  cout << endl;
  for (auto x : b2) {
    cout << hex << setw(2) << setfill(' ') << (int) x << " ";
  }
  cout << endl;

  auto  b3 = ~b2;
  for (auto x : b3) {
    cout << hex << setw(2) << setfill(' ') << (int) x << " ";
  }
  cout << endl;

  auto b4 = b2 + b3;
  for (auto x : b4) {
    cout << hex << setw(2) << setfill(' ') << (int) x << " ";
  }
  cout << endl;

  return 0;
}

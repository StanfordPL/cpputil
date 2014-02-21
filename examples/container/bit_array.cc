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

#include "include/container/bit_array.h"

using namespace cpputil;
using namespace std;

int main() {
  BitArray<9 * 8> b1;
  BitArray<9 * 8> b2;

  for (auto i = 0; i < 9; ++i) {
    b1.get_fixed_byte(i) = 0xff;
  }

  for (auto i = b1.fixed_byte_begin(), ie = b1.fixed_byte_end(); i != ie; ++i) {
    cout << hex << setw(2) << setfill(' ') << (int) *i << " ";
  }
  cout << endl;
  for (auto i = b2.fixed_byte_begin(), ie = b2.fixed_byte_end(); i != ie; ++i) {
    cout << hex << setw(2) << setfill(' ') << (int) *i << " ";
  }
  cout << endl;

  b2 |= b1;

  for (auto i = b1.fixed_byte_begin(), ie = b1.fixed_byte_end(); i != ie; ++i) {
    cout << hex << setw(2) << setfill(' ') << (int) *i << " ";
  }
  cout << endl;
  for (auto i = b2.fixed_byte_begin(), ie = b2.fixed_byte_end(); i != ie; ++i) {
    cout << hex << setw(2) << setfill(' ') << (int) *i << " ";
  }
  cout << endl;

  auto  b3 = ~b2;
  for (auto i = b3.fixed_byte_begin(), ie = b3.fixed_byte_end(); i != ie; ++i) {
    cout << hex << setw(2) << setfill(' ') << (int) *i << " ";
  }
  cout << endl;

  for (auto i = b1.set_bit_index_begin(); i != b1.set_bit_index_end(); ++i) {
    cout << dec << *i << " ";
  }
  cout << endl;

  return 0;
}

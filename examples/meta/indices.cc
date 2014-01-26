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

#include <array>
#include <iostream>

#include "include/meta/indices.h"

using namespace cpputil;
using namespace std;

template <size_t... Is>
std::array<int, sizeof...(Is)> make_array_helper(Indices<Is...>) {
  return {Is...};
}

template <size_t N>
std::array<int, N> make_array() {
  return make_array_helper(MakeIndices<N>());
}

int main() {
  for (auto i : make_array<10>()) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}

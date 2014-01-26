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
#include <unistd.h>

#include "include/lazy/thunk.h"

using namespace cpputil;
using namespace std;

int slow(int x) {
  sleep(x);
  return x;
}

int main() {
  auto t1 = make_thunk(slow, 3);
  cout << "Hello world!" << endl;
  cout << t1 << endl;

  return 0;
}

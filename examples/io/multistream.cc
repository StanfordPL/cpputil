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

#include "include/io/multistream.h"

using namespace cpputil;
using namespace std;

int main() {
  omultistream om;
  om << "You shouldn't see this" << endl;

  om.insert(cout);
  om << "You should see this" << endl;

  om.insert(cerr);
  om << "You should see this twice" << endl;

  return 0;
}

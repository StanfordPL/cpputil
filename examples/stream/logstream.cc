/*
Copyright 2013 eric schkufza

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <iostream>

#include "cpputil/stream/logstream.h"

using namespace cpputil;
using namespace std;

int main()
{
  ologstream os(cout);
	os.set_level(1);

  os << level(1) << "Should see this!" << endl;
  os << "As well as this (indented, no less)" << endl;
  os << "And this too." << endl;
  os << level(0) << ".. and this too!" << endl;
  
  os << level(2) << "Shouldn't see this!" << endl;

	os << level(0) << endl << level(1) << "What about these?" << endl << level(7) << "Definitely not this" << endl << level(0) << "But this.";

	cout << endl << "This should be left aligned" << endl;

  return 0;
}


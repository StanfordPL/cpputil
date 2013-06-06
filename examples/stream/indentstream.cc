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

#include "cpputil/stream/indentstream.h"

using namespace cpputil;
using namespace std;

int main()
{
  oindentstream os(cout);
	os << "Hello world" << endl;
	os << indent(2) << "Hello world (2)" << endl;
	os << indent(2) << "Hello world (4)" << endl;
	os << "Hello world (4)" << endl;
	os << unindent(4) << "Hello world (0)" << endl;
	os << indent(5) << unindent(10) << "Hello world (0)" << endl;
	os << indent(2) << "Hello world (2)" << endl;

	cout << "Hello world (0)" << endl;

  return 0;
}

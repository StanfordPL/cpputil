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

#include "cpputil/stream/redactstream.h"

using namespace cpputil;
using namespace std;

void print_secret(ostream& os)
{
	os << "Are you jaking me sideways while pumping my gas!?" << endl;
}

int main()
{
  oredactstream os(cout);

  os << "You should see this" << endl;
  os << redact << unredact << redact;

  os << "You shouldn't see this" << endl;
	print_secret(os);

  os << unredact;
  os << "You should see this" << endl;

	os << redact;
	cout << "You should see this" << endl;

  return 0;
}

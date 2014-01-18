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

#include "include/memory/interner.h"

using namespace cpputil;
using namespace std;

int main() {
  Interner<string> i;

  string s1 = "Hello";
  string s2 = "Hello";
  string s3 = "world";

  if ( &i.intern(s1) == &i.intern(s2) ) {
    cout << "These are the same string!" << endl;
	} else {
    cout << "Something is broken!" << endl;
	}

  if ( &i.intern(s1) == &i.intern(s3) ) {
    cout << "Something is broken!" << endl;
	} else {
    cout << "These are the same string!" << endl;
	}

	for ( int n = 0; n < 2; ++n ) {
		cout << "Interned strings: (" << i.size() << ") [ ";
		for ( const auto& itr : i )
			cout << itr << " ";
		cout << "]" << endl;

		i.clear();
	}

  return 0;
}

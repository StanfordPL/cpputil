#include <iostream>
#include <string>

#include "src/interner.h"

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

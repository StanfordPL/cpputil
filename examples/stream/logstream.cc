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


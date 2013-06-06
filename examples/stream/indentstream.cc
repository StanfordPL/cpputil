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

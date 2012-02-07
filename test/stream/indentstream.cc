#include <iostream>

#include "cpputil/stream/indentstream.h"

using namespace cpputil;
using namespace std;

int main()
{
  oindentstream os1(cout);
  os1.buf()->indent(2);
  oindentstream os(os1);

  os << "indent = 0";
  os.buf()->indent(1);

  os << endl << "indent = 1";
  os.buf()->indent(2);

  os << endl << "indent = 3";
  os.buf()->unindent(1);

  os << endl << "indent = 2";
  os.buf()->reset();

  os << endl << "indent = 0" << endl;

  return 0;
}

#include <iostream>

#include "cpputil/stream/teestream.h"

using namespace cpputil;
using namespace std;

int main()
{
  oteestream os(cout, cout);
  os << "[Should see this twice]" << endl;

  return 0;
}


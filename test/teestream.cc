#include <iostream>

#include "teestream.h"

using namespace cpputil;
using namespace std;

int main()
{
  teestream ts(cout, cout);
  ts << "[Should see this twice]" << endl;

  return 0;
}

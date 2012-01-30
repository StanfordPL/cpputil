#include <iostream>

#include "stream/shuntstream.h"

using namespace cpputil;
using namespace std;

int main()
{
  oshuntstream os(cout);

  os << "You should see this" << endl;
  os.buf()->close();
  os << "You shouldn't see this" << endl;
  os.buf()->open();
  os << "You should see this" << endl;

  return 0;
}

#include <iostream>

#include "forwardingstream.h"

using namespace cpputil;
using namespace std;

int main()
{
  forwardingstream fs(cout);

  fs.setActive(true);
  fs << "Should see this!" << endl;

  fs.setActive(false);
  fs << "Should not see this" << endl;

  return 0;
}

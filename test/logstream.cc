#include <iostream>

#include "logstream.h"

using namespace cpputil;
using namespace std;

int main()
{
  logstream ls(cout);
  ls << logstream::SEVERE << "Should see this!" << endl;
  ls << logstream::SEVERE << ".. and this too!" << endl;
  
  ls.setLevel(logstream::OFF);
  ls << logstream::SEVERE << "Shouldn't see this!" << endl;

  ls.setLevel(logstream::FINEST);
  ls << logstream::CONFIG << "But should see this!" << endl;
  ls << logstream::FINE << "... and this too!" << endl;

  ls << logstream::OFF << "Should not see this!" << endl;

  return 0;
}

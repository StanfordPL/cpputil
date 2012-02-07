#include <iostream>

#include "cpputil/stream/logstream.h"

using namespace cpputil;
using namespace std;

int main()
{
  ologstream os(cout);
  os << ologstream::SEVERE << "Should see this!" << endl;
  os << "As well as this (indented, no less)" << endl;
  os << "And this too." << endl;
  os << ologstream::SEVERE << ".. and this too!" << endl;
  
  os.setLevel(ologstream::OFF);
  os << ologstream::SEVERE << "Shouldn't see this!" << endl;

  os.setLevel(ologstream::FINEST);
  os << ologstream::CONFIG << "But should see this!" << endl;
  os << ologstream::FINE << "... and this too!" << endl;

  os.setLevel(ologstream::OFF);
  os << ologstream::SEVERE << "Should not see this!" << endl;

  return 0;
}


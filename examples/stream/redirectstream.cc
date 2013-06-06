#include <iostream>
#include <sstream>
#include <string>

#include "cpputil/stream/redirectstream.h"

using namespace cpputil;
using namespace std;

int main()
{
  oredirectstream ors(cout);
  ors << "Hello world!" << endl;

  istringstream iss("Hello world!");
  iredirectstream irs(iss);
  string s1, s2;

  irs >> s1 >> s2;
  cout << s1 << " " << s2 << endl;

  return 0;
}

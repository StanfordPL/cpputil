#include <iostream>
#include <sstream>
#include <string>

#include "cpputil/stream/delegatestream.h"

using namespace cpputil;
using namespace std;

int main()
{
  odelegatestream ods(cout);
  ods << "Hello world!" << endl;

  istringstream iss("Hello world!");
  idelegatestream ids(iss);
  string s1, s2;

  ids >> s1 >> s2;
  cout << s1 << " " << s2 << endl;

  return 0;
}

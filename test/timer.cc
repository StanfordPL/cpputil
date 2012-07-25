#include <iostream>

#include "cpputil/timer.h"

using namespace cpputil;
using namespace std;

int main()
{
  Timer t;

  t.start();
  for ( int i = 0; i < 1e9; ++i )
    ;
  t.stop();

  cout << t.sec() << endl;
  cout << t.nsec() << endl;

  return 0;
}

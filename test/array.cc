#include <iostream>

#include "array.h"

using namespace cpputil;
using namespace std;

int main()
{
  array<int, 10> x;

  for ( unsigned int i = 0, ie = x.size(); i < ie; ++i )
    x[i] = i;

  // Should print 0 .. 9
  for ( auto i = x.begin(), ie = x.end(); i != ie; ++i )
    cout << *i << endl;

  // Should print 9 .. 0
  for ( auto i = x.rbegin(), ie = x.rend(); i != ie; ++i )
    cout << *i << endl;

  return 0;
}

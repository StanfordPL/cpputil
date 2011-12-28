#include <iostream>
#include <map>

#include "maputil.h"

using namespace cpputil;
using namespace std;

void foo(const map<int, int>& m)
{
  cout << assert_at(m, 5) << endl;
}

int main()
{
  map<int, int> m;
  for ( auto i = 0; i < 10; ++i )
    m[i] = i;

  // Both should print 5
  cout << assert_at(m, 5) << endl;
  foo(m);
  cout.flush();

  // This should assert
  cout << assert_at(m, 20) << endl;

  return 0;
}

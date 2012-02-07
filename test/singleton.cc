#include <iostream>

#include "cpputil/singleton.h"

using namespace cpputil;
using namespace std;

int main()
{
  // Should print 10

  int& x = singleton<int>::get();
  x = 10;

  int& y = singleton<int>::get();
  cout << y << endl;

  return 0;
}

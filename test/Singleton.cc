#include <iostream>

#include "Singleton.h"

using namespace cpputil;
using namespace std;

int main()
{
  // Should print 10

  int& x = Singleton<int>::get();
  x = 10;

  int& y = Singleton<int>::get();
  cout << y << endl;

  return 0;
}

#include <iostream>

#include "cpputil/singleton.h"

using namespace cpputil;
using namespace std;

int main()
{
  // Should print 10

  auto& x = singleton<int>::get();
  x = 10;
  const auto& y = singleton<int>::get();
  auto& z = singleton<double>::get();
  z = 20;

  if ( y == 10 )
    cout << "Success!" << endl;
  else
    cout << "Failure!" << endl;

  return 0;
}

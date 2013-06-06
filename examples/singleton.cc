#include <iostream>

#include "src/singleton.h"

using namespace cpputil;
using namespace std;

int main() {
  auto& x = Singleton<int>::get();
  x = 10;
  const auto& y = Singleton<int>::get();
  auto& z = Singleton<double>::get();
  z = 20;

  if ( y == 10 )
    cout << "It works!" << endl;
  else
    cout << "It's broken!" << endl; 

  return 0;
}


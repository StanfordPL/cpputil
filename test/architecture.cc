#include <iostream>

#include "architecture.h"

using namespace std;

int main()
{
  #ifdef IS_64_BIT
    cout << "64 bits!" << endl;
  #else
    cout << "32 bits!" << endl;
  #endif

  return 0;
}

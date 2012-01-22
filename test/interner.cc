#include <iostream>
#include <sstream>
#include <string>

#include "Interner.h"

using namespace cpputil;
using namespace std;

int main()
{
  Interner<string> i;

  string s1 = "Hello";
  string s2 = "Hello";
  string s3 = "world";

  if ( &i.intern(s1) == &i.intern(s2) )
    cout << "It works!" << endl;
  else
    cout << "It doesn't work!" << endl;

  if ( &i.intern(s1) == &i.intern(s3) )
    cout << "It doesn't work!" << endl;
  else
    cout << "It works!" << endl;

  // Should print Hello world
  for ( auto itr : i )
    cout << itr << " ";
  cout << endl;

  Interner<string> i2;

  ostringstream oss;
  serialize(oss, i);

  istringstream iss(oss.str());
  deserialize(iss, i2);

  // Should also print Hello world
  for ( auto itr : i2 )
    cout << itr << " ";
  cout << endl;

  return 0;
}

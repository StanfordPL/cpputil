#include <iostream>
#include <string>

#include "bijection.h"

using namespace cpputil;
using namespace std;

int main()
{
  bijection<string, int> b;
  
  b.insert("Hello", 1);
  b.insert("World", 2);

  // Should print 0 2
  cout << b.empty() << " " << b.size() << endl;

  // Should print 1 0
  b.clear();
  cout << b.empty() << " " << b.size() << endl;

  string s = "";
  for ( auto i = 0; i < 10; ++i )
  {
    s += ('a' + i);
    b.insert(s, i); 
  }

  bijection<string, int> b2 = b;

  // Should print the map in order, and then backwards
  //for ( auto i = b2.beginDomain(), ie = b2.endDomain(); i != ie; ++i )
  //  cout << i->first << " " << *(i->second) << endl;
  //for ( auto i = b2.rbeginRange(), ie = b2.rendRange(); i != ie; ++i )
  //  cout << i->first << " " << *(i->second) << endl;

  // Should print 
  cout << *(b2.findDomain('a').second) << endl;
   

  return 0;
}

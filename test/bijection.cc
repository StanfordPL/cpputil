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

  // Should remove these two elements from future operations
  b2.eraseDomain("a");
  b2.eraseRange(7);

  // Should print the bijection in order, and then backwards
  for ( auto i = b2.beginDomain(), ie = b2.endDomain(); i != ie; ++i )
    cout << i->first << " " << *(i->second) << endl;
  for ( auto i = b2.rbeginRange(), ie = b2.rendRange(); i != ie; ++i )
    cout << i->first << " " << *(i->second) << endl;

  // Should print abc 2
  cout << *(b2.findRange(2)->second) << " " << *(b2.findDomain("abc")->second) << endl;

  // Should print abc 2
  cout << b2.assert_atRange(2) << " " << b2.assert_atDomain("abc") << endl;  

  return 0;
}

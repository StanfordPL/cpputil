#include <iostream>
#include <string>

#include "cpputil/bijection.h"

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
  b2.domain_erase("a");
  b2.range_erase(7);

  // Should print the bijection in order, and then backwards
  for ( auto itr : b2 )
    cout << itr.first << " " << itr.second << endl;
  for ( auto i = b2.rbegin(), ie = b2.rend(); i != ie; ++i )
    cout << i->first << " " << i->second << endl;

  // Should print just the domain, and then just the range
  for ( auto i = b2.domain_begin(), ie = b2.domain_end(); i != ie; ++i )
    cout << *i << endl;
  for ( auto i = b2.range_begin(), ie = b2.range_end(); i != ie; ++i )
    cout << *i << endl;

  // Should print abc 2
  cout << *b2.range_find(2) << " " << *b2.domain_find("abc") << endl;

  // Should print abc 2
  cout << b2.range_assert_at(2) << " " << b2.domain_assert_at("abc") << endl;  

  return 0;
}

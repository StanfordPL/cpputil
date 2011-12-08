#include <iostream>
#include <string>

#include "bimap.h"

using namespace cpputil;
using namespace std;

int main()
{
  bimap<string, int> bm;
  
  // Should print zero
  cout << bm.size() << endl;
  
  bm.insert("Hello", 1);
  bm.insert("World", 2);

  // Should print 2
  cout << bm.size() << endl;

  // Should print true,true,false
  cout << bm.containsKey("Hello") << " " << bm.containsVal(1) << endl;
  cout << bm.containsKey("World") << " " << bm.containsVal(2) << endl;
  cout << bm.containsKey("foo")   << " " << bm.containsVal(3) << endl;

  bm.clear();

  // Should print 0
  cout << bm.size() << endl;

  // Should print false, false, false
  cout << bm.containsKey("Hello") << " " << bm.containsVal(1) << endl;
  cout << bm.containsKey("World") << " " << bm.containsVal(2) << endl;
  cout << bm.containsKey("foo")   << " " << bm.containsVal(3) << endl;

  string s = "";
  for ( int i = 0; i < 10; ++i )
  {
    s += ('a' + i);
    bm.insert(s, i);
  }

  // Should print 2
  cout << bm.getVal("abc") << endl;

  // Should print "abcdefghij"
  cout << bm.getKey(9) << endl;

  // Should print false, false
  bm.eraseKey("abc");
  bm.eraseVal(3);
  cout << bm.containsKey("abc") << " " << bm.containsVal(2) << endl;
  cout << bm.containsKey("abcd") << " " << bm.containsVal(3) << endl;

  return 0;
}

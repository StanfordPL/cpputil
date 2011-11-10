#include <iostream>
#include <string>

#include "BiMap.h"

using namespace std;

int main()
{
  BiMap<string, int> bm;
  
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

  // Should print "a", 0 ... "j", 9
  for ( auto i = bm.begin(), ie = bm.end(); i != ie; ++i )
    cout << (*i).first << " " << (*i).second << endl;

  // Should print 2
  cout << bm.getVal("abc") << endl;

  // Should print "abcdefghij"
  cout << bm.getKey(9) << endl;

  return 0;
}

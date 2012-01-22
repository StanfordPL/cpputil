#include <iostream>
#include <sstream>
#include <string>

#include "Histogram.h"

using namespace cpputil;
using namespace std;

int main()
{
  Histogram<string> h;
  h.insert("hello", 10);
  h.insert("world", 20);
  h.insert("foo", 30);
  h.insert("hello", 1);
  h.insert("world", 2);
  h.insert("foo", 3);

  // Should print hello 11, world 22, foo 33
  for ( auto itr : h )
    cout << itr.first << " " << itr.second << " ";
  cout << endl;

  Histogram<string> h2 = h;

  // Should print hello 11, world 22, foo 33, baz 44
  h2.insert("baz", 44);
  for ( auto itr : h2 )
    cout << itr.first << " " << itr.second << " ";
  cout << endl;

  h += h2;

  // Should print hello 22, world 44, foo 66, baz 44
  for ( auto itr : h )
    cout << itr.first << " " << itr.second << " ";
  cout << endl;

  Histogram<string> h3 = h + h2;

  // Should print hello 33, world 66, foo 99, baz 88
  for ( auto itr : h3 )
    cout << itr.first << " " << itr.second << " ";
  cout << endl;

  ostringstream oss;
  serialize(oss, h3);
  istringstream iss(oss.str());

  Histogram<string> h4;
  deserialize(iss, h4);
    
  // Should print the same
  for ( auto itr : h4 )
    cout << itr.first << " " << itr.second << " ";
  cout << endl;

  return 0;
}

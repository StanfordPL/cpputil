#include <iostream>
#include <list>
#include <string>

#include "stringutil.h"

using namespace cpputil;
using namespace std;

int main()
{
  cout << itoa(-20) << endl;
  cout << utoa(20) << endl; 

  const char* s1 = "one two three";
  const char* s2 = "four\nfive\nsix";
  list<string> ls;

  words(s1, ls);
  lines(s2, ls); 

  for ( auto i : ls )
    cout << i << endl;

  cout << "[" << unwords(ls.begin(), ls.end()) << "]" << endl;
  cout << "[" << unlines(ls.begin(), ls.end()) << "]" << endl;

  return 0;
}

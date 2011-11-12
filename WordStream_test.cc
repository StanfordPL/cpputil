#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "WordStream.h"

using namespace std;

int main()
{
  OWordStream ows;
  ows << "Hello" << "World" << "foo";

  // Should print "[Hello World foo]"
  cout << "[" << ows.str() << "]" << endl;

  IWordStream iws(ows.str());
  string s;

  // Should print out "Hello", "World", "foo"
  while ( !iws.eof() )
  {
    iws >> s;
    cout << "[" << s << "]" << endl;
  }

  string as = "a a a a a a a a a a";

  list<string> ls;
  vector<string> vs;

  words(as, ls);
  words(as, vs);

  // Should both print "[a.a.a.a.a.a.a.a.a.a]"
  cout << "[" << unwords(ls.begin(), ls.end(), '.') << "]" << endl;
  cout << "[" << unwords(vs.begin(), vs.end(), '.') << "]" << endl;

  return 0;
}

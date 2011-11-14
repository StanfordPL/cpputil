#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include "WordStream.h"

using namespace std;

int main()
{
  ostringstream oss;
  OWordStream ows(oss);
  ows << "Hello" << "World" << "foo";

  // Should print "[Hello World foo]"
  cout << "[" << oss.str() << "]" << endl;

  istringstream iss(oss.str());
  IWordStream iws(iss);
  string s;

  // Should print out "Hello", "World", "foo"
  while ( !iss.eof() )
  {
    iws >> s;
    cout << "[" << s << "]" << endl;
  }

  string as = "1 1 1 1 1 1 1 1 1 1";

  list<int> ls;
  vector<int> vs;

  words(as, ls, ' ');
  words(as, vs, ' ');

  // Should both print "[1.1.1.1.1.1.1.1.1.1]"
  cout << "[" << unwords(ls.begin(), ls.end(), '.') << "]" << endl;
  cout << "[" << unwords(vs.begin(), vs.end(), '.') << "]" << endl;

  return 0;
}

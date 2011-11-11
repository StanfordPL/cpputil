#include <iostream>

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

  return 0;
}

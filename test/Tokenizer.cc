#include <iostream>
#include <string>

#include "Tokenizer.h"

using namespace cpputil;
using namespace std;

int main()
{
  Tokenizer<string> t;

  // Should print 1 0
  cout << t.empty() << " " << t.size() << endl;

  // Should print 0 1 2
  cout << t.tokenize("Hello") << " ";
  cout << t.tokenize("World") << " ";
  cout << t.tokenize("foo")   << endl;

  // Should print "Hello World foo"
  cout << t.untokenize(0) << " ";
  cout << t.untokenize(1) << " ";
  cout << t.untokenize(2) << endl;

  // Should print 0 3
  cout << t.empty() << " " << t.size() << endl;

  // Should print 1 0
  t.clear();
  cout << t.empty() << " " << t.size() << endl;

  return 0;
}

#include <iostream>
#include <string>

#include "tokenizer.h"

using namespace cpputil;
using namespace std;

int main()
{
  tokenizer<string> t;

  // Should print 1 0
  cout << t.empty() << " " << t.size() << endl;

  // Should print 0 1 2
  cout << t.tokenize("Hello") << " ";
  cout << t.tokenize("World") << " ";
  cout << t.tokenize("foo")   << endl;

  tokenizer<string> t2 = t;

  // Should print "Hello World foo"
  cout << t2.untokenize(0) << " ";
  cout << t2.untokenize(1) << " ";
  cout << t2.untokenize(2) << endl;

  // Should print "Hello World foo"
  for ( auto i = t2.begin(), ie = t2.end(); i != ie; ++i )
    cout << *i << " ";
  cout << endl;

  // Should print 0 3
  cout << t2.empty() << " " << t.size() << endl;

  // Should print 1 0
  t2.clear();
  cout << t2.empty() << " " << t.size() << endl;

  return 0;
}

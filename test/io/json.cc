#include <iostream>
#include <deque>
#include <map>
#include <string>
#include <vector>

#include "cpputil/io/json.h"

using namespace cpputil;
using namespace std;

int main()
{
  vector<char> v;
  for ( auto i = 0; i < 10; ++i )
    v.push_back('a' + i);

  deque<string> d;
  d.push_back("hello");
  d.push_back("world");
  d.push_back("foo");
  d.push_back("bar");
  d.push_back("baz");

  map<int, double> m;
  for ( auto i = 0; i < 10; ++i )
    m[i] = i + 0.5;

  map<deque<string>, char> m2;
  m2[d] = 'c';

  map<deque<string>, vector<char>> m3;
  m3[d] = v;

  cout << jsonwriter(d) << endl;
  cout << jsonwriter(v) << endl;
  cout << jsonwriter(m) << endl;
  cout << jsonwriter(m2) << endl;
  cout << jsonwriter(m3) << endl;

  return 0;
}


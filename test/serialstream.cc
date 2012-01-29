#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <string>

#include "serialstream.h"

using namespace cpputil;
using namespace std;

int main()
{
  oserialstream oss(cout);

  string str = "Hello";
  oss << str << endl;
  oss << "Hello world!" << endl;
  const char* c = "Hello world foo bar";

  deque<int> d;
  d.push_back(1);
  d.push_back(2);

  set<float> s;
  s.insert(1.0);
  s.insert(2.5);
  s.insert(5.0);

  map<set<float>, deque<int>> m;
  m[s] = d;

  pair<string, map<set<float>, deque<int>>> p;
  p = make_pair("Hello", m);

  oss << c << '\n' << d << '\n' << s << '\n' << m << '\n' << p << '\n';

  return 0;
}

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <sstream>

#include "io/serial.h"

using namespace cpputil;
using namespace std;

int main()
{
  cout << serialwriter(1) << endl;
  cout << serialwriter(string("Hello world!")) << endl;

  vector<int> v;
  for ( auto i = 0; i < 10; ++i )
    v.push_back(i);
  cout << serialwriter(v) << endl;
  
  set<string> s;
  s.insert("Hello");
  s.insert("World");
  cout << serialwriter(s) << endl;

  list<set<string>> l;
  l.push_back(s);
  l.push_back(s);
  cout << serialwriter(l) << endl;

  map<list<set<string>>, vector<int>> m;
  m[l] = v;
  cout << serialwriter(m) << endl;

  ostringstream oss;
  oss << serialwriter(m);
  
  istringstream iss(oss.str());
  map<list<set<string>>, vector<int>> m2;
  iss >> serialreader(m2);

  cout << serialwriter(m2) << endl;

  return 0;
}

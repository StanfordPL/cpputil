#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <sstream>

#include "cpputil/io/serial.h"

using namespace cpputil;
using namespace std;

int main()
{
  cout << serialwriter<int, '$'>(1) << endl;
  cout << serialwriter<string, '$'>(string("Hello world!")) << endl;

  vector<int> v;
  for ( auto i = 0; i < 10; ++i )
    v.push_back(i);
  cout << serialwriter<vector<int>, '$'>(v) << endl;
  
  set<string> s;
  s.insert("Hello");
  s.insert("World");
  cout << serialwriter<set<string>, '$'>(s) << endl;

  list<set<string>> l;
  l.push_back(s);
  l.push_back(s);
  cout << serialwriter<list<set<string>>, '$'>(l) << endl;

  map<list<set<string>>, vector<int>> m;
  m[l] = v;
  cout << serialwriter<map<list<set<string>>, vector<int>>, '$'>(m) << endl;

  ostringstream oss;
  oss << serialwriter<map<list<set<string>>, vector<int>>, '$'>(m);
  
  istringstream iss(oss.str());
  map<list<set<string>>, vector<int>> m2;
  iss >> serialreader<map<list<set<string>>, vector<int>>, '$'>(m2);

  cout << serialwriter<map<list<set<string>>, vector<int>>, '$'>(m2) << endl;

  return 0;
}

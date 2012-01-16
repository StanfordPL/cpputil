#include <iostream>
#include <sstream>

#include "serialize.h"

using namespace cpputil;
using namespace std;

template <typename _Sequence>
void tests(_Sequence s)
{
  for ( auto i = 0; i < 10; ++i )
    s.push_back(i);
  
  ostringstream oss;
  oss << s;

  cout << "[" << oss.str() << "]" << endl;

  istringstream iss(oss.str());
  iss >> s;

  for ( auto v : s )
    cout << v << " ";
  cout << endl;
}

template <typename _Associative>
void testa(_Associative a)
{
  for ( auto i = 0; i < 10; ++i )
    a[i] = i;

  ostringstream oss;
  oss << a;

  cout << "[" << oss.str() << "]" << endl;

  istringstream iss(oss.str());
  iss >> a;

  for ( auto v : a )
    cout << "(" << v.first << ", " << v.second << ") ";
  cout << endl;
}

int main()
{
  map<int, int> m;
  vector<int> v;

  testa(m);
  tests(v);

  return 0;
}

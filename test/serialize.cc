#include <iostream>
#include <sstream>

#include "serialize.h"

using namespace cpputil;
using namespace std;

template <typename _Sequence>
void tests(_Sequence& s)
{
  for ( auto i = 0; i < 10; ++i )
    s.push_back(i);
  
  ostringstream oss;
  serialize(oss, s);

  cout << "[" << oss.str() << "]" << endl;

  istringstream iss(oss.str());
  deserialize(iss, s);

  for ( auto v : s )
    cout << v << " ";
  cout << endl;
}

template <typename _Associative>
void testa(_Associative& a)
{
  for ( auto i = 0; i < 10; ++i )
    a[i] = i;

  ostringstream oss;
  serialize(oss, a);

  cout << "[" << oss.str() << "]" << endl;

  istringstream iss(oss.str());
  deserialize(iss, a);

  for ( auto v : a )
    cout << "(" << v.first << ", " << v.second << ") ";
  cout << endl;
}

template <typename _T>
void testt(tokenizer<_T>& t)
{
  const char* vals[3] = { "[element one]", "[element two]", "[element 3]" };

  for ( auto i = 0; i < 3; ++i )
    t.tokenize(vals[i]);

  ostringstream oss;
  serialize(oss, t);

  cout << "[" << oss.str() << "]" << endl;

  istringstream iss(oss.str());
  deserialize(iss, t);

  for ( auto v : t )
    cout << v << " ";
  cout << endl;
}

int main()
{
  map<int, int> m;
  vector<int> v;
  tokenizer<string> t;

  testa(m);
  tests(v);
  testt(t);

  return 0;
}

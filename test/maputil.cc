#include <iostream>
#include <map>

#include "cpputil/maputil.h"

using namespace cpputil;
using namespace std;

void foo(const map<int, int>& m)
{
  cout << assert_at(m, 5) << endl;
}

int main()
{
  map<int, int> m;
  for ( auto i = 0; i < 10; ++i )
    m[i] = i;

  // These should all print 0 .. 9
  for ( auto i = const_key_iterator<map<const int, int>>(m.begin()), ie = const_key_iterator<map<const int, int>>(m.end()); i != ie; ++i )
    cout << *i << " ";
  cout << endl;
  for ( auto i = value_iterator<map<const int, int>>(m.begin()), ie = value_iterator<map<const int, int>>(m.end()); i != ie; ++i )
    cout << *i << " ";
  cout << endl;
  for ( auto i = const_value_iterator<map<const int, int>>(m.begin()), ie = const_value_iterator<map<const int, int>>(m.end()); i != ie; ++i )
    cout << *i << " ";
  cout << endl;

  // These should all print 9 .. 0
  for ( auto i = const_reverse_key_iterator<map<const int, int>>(m.rbegin()), ie = const_reverse_key_iterator<map<const int, int>>(m.rend()); i != ie; ++i )
    cout << *i << " ";
  cout << endl;
  for ( auto i = reverse_value_iterator<map<const int, int>>(m.rbegin()), ie = reverse_value_iterator<map<const int, int>>(m.rend()); i != ie; ++i )
    cout << *i << " ";
  cout << endl;
  for ( auto i = const_reverse_value_iterator<map<const int, int>>(m.rbegin()), ie = const_reverse_value_iterator<map<const int, int>>(m.rend()); i != ie; ++i )
    cout << *i << " ";
  cout << endl;

  // Both should print 5
  cout << assert_at(m, 5) << endl;
  foo(m);
  cout.flush();

  // This should assert
  cout << assert_at(m, 20) << endl;

  return 0;
}

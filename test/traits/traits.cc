#include <iostream>
#include <vector>

#include "traits/traits.h"

using namespace cpputil;
using namespace std;

template <typename Ch, typename Tr, typename T>
typename std::enable_if<std::is_scalar<T>::value, void>::type
/*void*/ foo(std::basic_ostream<Ch, Tr>& os, const T& t, char delim = '"')
{
  os << "Is scalar type!" << endl;
  os << t << endl;
}

template <typename Ch, typename Tr, typename T>
typename std::enable_if<is_stl_container<typename std::remove_const<T>::type>::value, void>::type
/*void*/ foo(std::basic_ostream<Ch, Tr>& os, const T& t, char delim = '"')
{
  os << "Is stl container type!" << endl;
  os << t << endl;
}


int main()
{
  foo(cout, 1);

  return 0;
}

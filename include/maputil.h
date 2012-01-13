#ifndef MAP_UTIL_H
#define MAP_UTIL_H

#include <cassert>

namespace cpputil
{

template <typename _Associative>
inline typename _Associative::value_type::second_type& assert_at(_Associative& a, const typename _Associative::value_type::first_type& key)
{
  assert(a.find(key) != a.end() && "Unrecognized key!");
  return a.find(key)->second;
}

template <typename _Associative>
inline const typename _Associative::value_type::second_type& assert_at(const _Associative& a, const typename _Associative::value_type::first_type& key)
{
  assert(a.find(key) != a.end() && "Unrecognized key!");
  return a.find(key)->second;
}

template <typename _Associative>
inline typename _Associative::size_type erase_at(const _Associative& a, const typename _Associative::value_type::first_type& key)
{
  assert(a.find(key) != a.end() && "Unrecognized key!");
  return a.erase(key);
}

}

#endif

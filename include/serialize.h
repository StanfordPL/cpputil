#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <cassert>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

namespace cpputil
{

template <typename _T>
void serialize(std::ostream& os, const _T& t)
{
  os << t;
}

template <typename _T>
void serialize(std::ostream& os, const std::deque<_T>& ts)
{
  os << ts.size() << " ";
  for ( auto t : ts )
  {
    serialize(os, t);
    os << " ";
  }
}

template <typename _T>
void serialize(std::ostream& os, const std::list<_T>& ts)
{
  os << ts.size() << " ";
  for ( auto t : ts )
  {
    serialize(os, t);
    os << " ";
  }
}

template <typename _Key, typename _Val>
void serialize(std::ostream& os, const std::map<_Key, _Val>& m)
{
  os << m.size() << " ";
  for ( auto p : m )
  {
    serialize(os, p.first);
    os << " ";
    serialize(os, p.second);
    os << " ";
  }
}

template <typename _T>
void serialize(std::ostream& os, const std::set<_T>& ts)
{
  os << ts.size() << " ";
  for ( auto t : ts )
  {
    serialize(os, t);
    os << " ";
  }
}

template <typename _T>
void serialize(std::ostream& os, const std::vector<_T>& ts)
{
  os << ts.size() << " ";
  for ( auto t : ts )
  {
    serialize(os, t);
    os << " ";
  }
}

template <typename _T>
void deserialize(std::istream& is, _T& t)
{
  is >> t;
}

template <typename _T>
void deserialize(std::istream& is, std::deque<_T>& ts)
{
  ts.clear();

  typename std::deque<_T>::size_type size;
  is >> size;

  _T t;
  for ( auto i = 0; i < size; ++i )
  {
    deserialize(is, t);
    ts.emplace_back(t);
  }
}

template <typename _T>
void deserialize(std::istream& is, std::list<_T>& ts)
{
  ts.clear();

  typename std::list<_T>::size_type size;
  is >> size;

  _T t;
  for ( auto i = 0; i < size; ++i )
  {
    deserialize(is, t);
    ts.emplace_back(t);
  }
}

template <typename _Key, typename _Val>
void deserialize(std::istream& is, std::map<_Key, _Val>& m)
{
  m.clear();

  typename std::map<_Key, _Val>::size_type size;
  is >> size;

  _Key key;
  _Val val;
  for ( auto i = 0; i < size; ++i )
  {
    deserialize(is, key);
    deserialize(is, val);
    m[key] = val;
  }
}

template <typename _T>
void deserialize(std::istream& is, std::set<_T>& ts)
{
  ts.clear();

  typename std::set<_T>::size_type size;
  is >> size;

  _T t;
  for ( auto i = 0; i < size; ++i )
  {
    deserialize(is, t);
    ts.insert(t);
  }
}

template <typename _T>
void deserialize(std::istream& is, std::vector<_T>& ts)
{
  ts.clear();

  typename std::vector<_T>::size_type size;
  is >> size;
  ts.reserve(size);

  _T t;
  for ( auto i = 0; i < size; ++i )
  {
    deserialize(is, t);
    ts.emplace_back(t);
  }
}

} 

#endif

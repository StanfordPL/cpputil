#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <cassert>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

#include "tokenizer.h"

namespace cpputil
{

template <typename _T>
std::ostream& operator<<(std::ostream& os, const std::deque<_T>& ts)
{
  os << ts.size() << " ";
  for ( auto t : ts )
    os << t << " ";

  return os;
}

template <typename _T>
std::ostream& operator<<(std::ostream& os, const std::list<_T>& ts)
{
  os << ts.size() << " ";
  for ( auto t : ts )
    os << t << " ";

  return os;
}

template <typename _Key, typename _Val>
std::ostream& operator<<(std::ostream& os, const std::map<_Key, _Val>& m)
{
  os << m.size() << " ";
  for ( auto p : m )
    os << p.first << " " << p.second << " ";

  return os;
}

template <typename _T>
std::ostream& operator<<(std::ostream& os, const std::set<_T>& ts)
{
  os << ts.size() << " ";
  for ( auto t : ts )
    os << t << " ";

  return os;
}

template <typename _T>
std::ostream& operator<<(std::ostream& os, const tokenizer<_T>& ts)
{
  os << ts.size() << " ";
  for ( auto t : ts )
    os << t << " ";

  return os;
}

template <typename _T>
std::ostream& operator<<(std::ostream& os, const std::vector<_T>& ts)
{
  os << ts.size() << " ";
  for ( auto t : ts )
    os << t << " ";

  return os;
}

template <typename _T>
std::istream& operator>>(std::istream& is, std::deque<_T>& ts)
{
  ts.clear();

  typename std::deque<_T>::size_type size;
  is >> size;

  _T t;
  for ( auto i = 0; i < size; ++i )
  {
    is >> t;
    ts.emplace_back(t);
  }

  return is;
}

template <typename _T>
std::istream& operator>>(std::istream& is, std::list<_T>& ts)
{
  ts.clear();

  typename std::list<_T>::size_type size;
  is >> size;

  _T t;
  for ( auto i = 0; i < size; ++i )
  {
    is >> t;
    ts.emplace_back(t);
  }

  return is;
}

template <typename _Key, typename _Val>
std::istream& operator>>(std::istream& is, std::map<_Key, _Val>& m)
{
  m.clear();

  typename std::map<_Key, _Val>::size_type size;
  is >> size;

  _Key key;
  _Val val;
  for ( auto i = 0; i < size; ++i )
  {
    is >> key >> val;
    m[key] = val;
  }

  return is;
}

template <typename _T>
std::istream& operator>>(std::istream& is, std::set<_T>& ts)
{
  ts.clear();

  typename std::set<_T>::size_type size;
  is >> size;

  _T t;
  for ( auto i = 0; i < size; ++i )
  {
    is >> t;
    ts.insert(t);
  }

  return is;
}

template <typename _T>
std::istream& operator>>(std::istream& is, tokenizer<_T>& ts)
{
  ts.clear();

  typename tokenizer<_T>::size_type size;
  is >> size;
  
  _T t;
  for ( auto i = 0; i < size; ++i )
  {
    is >> t;
    ts.tokenize(t);
  }

  return is;
}

template <typename _T>
std::istream& operator>>(std::istream& is, std::vector<_T>& ts)
{
  ts.clear();

  typename std::vector<_T>::size_type size;
  is >> size;
  ts.reserve(size);

  _T t;
  for ( auto i = 0; i < size; ++i )
  {
    is >> t;
    ts.emplace_back(t);
  }

  return is;
}

} 

#endif

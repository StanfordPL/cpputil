#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "tokenizer.h"

namespace cpputil
{

template <typename _T>
void serialize(std::ostream& os, const _T& t, char delim = '"')
{
  os << t;
}

template <typename _T>
void serialize(std::ostream& os, const std::deque<_T>& ts, char delim = '"')
{
  os << ts.size() << " ";
  for ( auto t : ts )
  {
    serialize(os, t, delim);
    os << " ";
  }
}

template <typename _T>
void serialize(std::ostream& os, const std::list<_T>& ts, char delim = '"')
{
  os << ts.size() << " ";
  for ( auto t : ts )
  {
    serialize(os, t, delim);
    os << " ";
  }
}

template <typename _Key, typename _Val>
void serialize(std::ostream& os, const std::map<_Key, _Val>& m, char delim = '"')
{
  os << m.size() << " ";
  for ( auto p : m )
  {
    serialize(os, p.first, delim);
    os << " ";
    serialize(os, p.second, delim);
    os << " ";
  }
}

template <typename _T>
void serialize(std::ostream& os, const std::set<_T>& ts, char delim = '"')
{
  os << ts.size() << " ";
  for ( auto t : ts )
  {
    serialize(os, t, delim);
    os << " ";
  }
}

void serialize(std::ostream& os, const std::string& s, char delim = '"')
{
  os << delim << s << delim;
}

template <typename _T>
void serialize(std::ostream& os, const tokenizer<_T>& ts, char delim = '"')
{
  os << ts.size() << " ";
  for ( auto t : ts )
  {
    serialize(os, t, delim);
    os << " ";
  }
}

template <typename _T>
void serialize(std::ostream& os, const std::vector<_T>& ts, char delim = '"')
{
  os << ts.size() << " ";
  for ( auto t : ts )
  {
    serialize(os, t, delim);
    os << " ";
  }
}

template <typename _T>
void deserialize(std::istream& is, _T& t, char delim = '"')
{
  is >> t;
}

template <typename _T>
void deserialize(std::istream& is, std::deque<_T>& ts, char delim = '"')
{
  ts.clear();

  typename std::deque<_T>::size_type size;
  is >> size;
  
  _T t;
  for ( auto i = 0; i < size; ++i )
  {
    deserialize(is, t, delim);
    ts.emplace_back(t);
  }
}

template <typename _T>
void deserialize(std::istream& is, std::list<_T>& ts, char delim = '"')
{
  ts.clear();

  typename std::list<_T>::size_type size;
  is >> size;

  _T t;
  for ( auto i = 0; i < size; ++i )
  {
    deserialize(is, t, delim);
    ts.emplace_back(t);
  }
}

template <typename _Key, typename _Val>
void deserialize(std::istream& is, std::map<_Key, _Val>& m, char delim = '"')
{
  m.clear();

  typename std::map<_Key, _Val>::size_type size;
  is >> size;

  _Key key;
  _Val val;
  for ( auto i = 0; i < size; ++i )
  {
    deserialize(is, key, delim);
    deserialize(is, val, delim);
    m[key] = val;
  }
}

template <typename _T>
void deserialize(std::istream& is, std::set<_T>& ts, char delim = '"')
{
  ts.clear();

  typename std::set<_T>::size_type size;
  is >> size;

  _T t;
  for ( auto i = 0; i < size; ++i )
  {
    deserialize(t);
    ts.insert(t);
  }
}

void deserialize(std::istream& is, std::string& s, char delim = '"')
{
  getline(is, s, delim);
  getline(is, s, delim);
}

template <typename _T>
void deserialize(std::istream& is, tokenizer<_T>& ts, char delim = '"')
{
  ts.clear();

  typename tokenizer<_T>::size_type size;
  is >> size;
  
  _T t;
  for ( auto i = 0; i < size; ++i )
  {
    deserialize(is, t, delim);
    ts.tokenize(t);
  }
}

template <typename _T>
void deserialize(std::istream& is, std::vector<_T>& ts, char delim = '"')
{
  ts.clear();

  typename std::vector<_T>::size_type size;
  is >> size;
  ts.reserve(size);

  _T t;
  for ( auto i = 0; i < size; ++i )
  {
    deserialize(is, t, delim);
    ts.emplace_back(t);
  }
}

} 

#endif

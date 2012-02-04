#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace cpputil
{

  // TODO: This header is deprecated!  Don't use it!

template <typename _T>
struct Serializer
{
  static void serialize(std::ostream& os, const _T& t, char delim = '"')
  {
    os << t;
  }
};

template <typename _Char, typename _Traits>
struct Serializer<std::basic_string<_Char, _Traits>>
{
  static void serialize(std::ostream& os, const std::basic_string<_Char, _Traits>& s, char delim = '"') 
  { 
    os << delim << s << delim; 
  }
};

template <typename _T>
struct Serializer<std::deque<_T>>
{
  static void serialize(std::ostream& os, const std::deque<_T>& ts, char delim = '"')
  {
    os << ts.size() << " ";
    for ( auto t : ts )
    {
      Serializer<_T>::serialize(os, t, delim);
      os << " ";
    }
  }
};

template <typename _T>
struct Serializer<std::list<_T>>
{
  static void serialize(std::ostream& os, const std::list<_T>& ts, char delim = '"')
  {
    os << ts.size() << " ";
    for ( auto t : ts )
    {
      Serializer<_T>::serialize(os, t, delim);
      os << " ";
    }
  }
};

template <typename _T1, typename _T2>
struct Serializer<std::map<_T1, _T2>>
{
  static void serialize(std::ostream& os, const std::map<_T1, _T2>& m, char delim = '"')
  {
    os << m.size() << " ";
    for ( auto p : m )
    {
      Serializer<std::pair<_T1, _T2>>::serialize(os, p, delim);
      os << " ";
    }
  }
};

template <typename _T1, typename _T2>
struct Serializer<std::pair<_T1, _T2>>
{
  static void serialize(std::ostream& os, const std::pair<_T1, _T2>& p, char delim = '"')
  {
    Serializer<_T1>::serialize(os, p.first, delim);
    os << " ";
    Serializer<_T2>::serialize(os, p.second, delim);
  }
};

template <typename _T>
struct Serializer<std::set<_T>>
{
  static void serialize(std::ostream& os, const std::set<_T>& ts, char delim = '"')
  {
    os << ts.size() << " ";
    for ( auto t : ts )
    {
      Serializer<_T>::serialize(os, t, delim);
      os << " ";
    }
  }
};

template <typename _T>
struct Serializer<std::vector<_T>>
{
  static void serialize(std::ostream& os, const std::vector<_T>& ts, char delim = '"')
  {
    os << ts.size() << " ";
    for ( auto t : ts )
    {
      Serializer<_T>::serialize(os, t, delim);
      os << " ";
    }
  }
};

template <typename _T>
void serialize(std::ostream& os, const _T& t, char delim = '"')
{
  Serializer<_T>::serialize(os, t, delim);
}

template <typename _T>
struct Deserializer
{
  static void deserialize(std::istream& is, _T& t, char delim = '"')
  {
    is >> t;
  }
};

template <typename _Char, typename _Traits>
struct Deserializer<std::basic_string<_Char, _Traits>>
{
  static void deserialize(std::istream& is, std::basic_string<_Char, _Traits>& s, char delim = '"')
  {
    getline(is, s, delim);
    getline(is, s, delim);
  }
};

template <typename _T>
struct Deserializer<std::deque<_T>>
{
  static void deserialize(std::istream& is, std::deque<_T>& ts, char delim = '"')
  {
    ts.clear();

    typename std::deque<_T>::size_type size;
    is >> size;

    _T t;
    for ( typename std::deque<_T>::size_type i = 0; i < size; ++i )
    {
      Deserializer<_T>::deserialize(is, t, delim);
      ts.emplace_back(t);
    }
  }
};

template <typename _T>
struct Deserializer<std::list<_T>>
{
  static void deserialize(std::istream& is, std::list<_T>& ts, char delim = '"')
  {
    ts.clear();

    typename std::list<_T>::size_type size;
    is >> size;

    _T t;
    for ( typename std::list<_T>::size_type i = 0; i < size; ++i )
    {
      Deserializer<_T>::deserialize(is, t, delim);
      ts.emplace_back(t);
    }
  }
};

template <typename _T1, typename _T2>
struct Deserializer<std::map<_T1, _T2>>
{
  static void deserialize(std::istream& is, std::map<_T1, _T2>& m, char delim = '"')
  {
    m.clear();

    typename std::map<_T1, _T2>::size_type size;
    is >> size;

    std::pair<_T1, _T2> p;
    for ( typename std::map<_T1, _T2>::size_type i = 0; i < size; ++i )
    {
      Deserializer<std::pair<_T1, _T2>>::deserialize(is, p, delim);
      m.insert(p);
    }
  }
};

template <typename _T1, typename _T2>
struct Deserializer<std::pair<_T1, _T2>>
{
  static void deserialize(std::istream& is, std::pair<_T1, _T2>& p, char delim = '"')
  {
    Deserializer<_T1>::deserialize(is, p.first, delim);
    Deserializer<_T2>::deserialize(is, p.second, delim);
  }
};

template <typename _T>
struct Deserializer<std::set<_T>>
{
  static void deserialize(std::istream& is, std::set<_T>& ts, char delim = '"')
  {
    ts.clear();

    typename std::set<_T>::size_type size;
    is >> size;

    _T t;
    for ( typename std::set<_T>::size_type i = 0; i < size; ++i )
    {
      Deserializer<_T>::deserialize(is, t, delim);
      ts.insert(t);
    }
  }
};

template <typename _T>
struct Deserializer<std::vector<_T>>
{
  static void deserialize(std::istream& is, std::vector<_T>& ts, char delim = '"')
  {
    ts.clear();

    typename std::vector<_T>::size_type size;
    is >> size;
    ts.reserve(size);

    _T t;
    for ( typename std::vector<_T>::size_type i = 0; i < size; ++i )
    {
      Deserializer<_T>::deserialize(is, t, delim);
      ts.emplace_back(t);
    }
  }
};

template <typename _T>
void deserialize(std::istream& is, _T& t, char delim = '"')
{
  Deserializer<_T>::deserialize(is, t, delim);
}

} 

#endif

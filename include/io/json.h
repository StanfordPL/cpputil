#ifndef JSON_H
#define JSON_H

#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace cpputil
{

template <typename _T>
struct Json
{
  static void json(std::ostream& os, const _T& t)
  {
    os << t;
  }
};

template <>
struct Json<char>
{
  static void json(std::ostream& os, char c)
  {
    os << "\"" << c << "\"";
  }
};

template <>
struct Json<bool>
{
  static void json(std::ostream& os, bool b)
  {
    os << (b ? "true" : "false");
  }
};

template <typename _Char, typename _Traits>
struct Json<std::basic_string<_Char, _Traits>>
{
  static void json(std::ostream& os, const std::basic_string<_Char, _Traits>& s)
  {
    os << "\"" << s << "\"";
  }
};

template <typename _T>
struct Json<std::deque<_T>>
{
  static void json(std::ostream& os, const std::deque<_T>& ts)
  {
    os << "[";
    for ( auto i = ts.begin(), ie = ts.end(); i != ie; ++i )
    {
      if ( i != ts.begin() )
        os << ",";
      Json<_T>::json(os, *i);
    }
    os << "]";
  }
};

template <typename _T>
struct Json<std::list<_T>>
{
  static void json(std::ostream& os, const std::list<_T>& ts)
  {
    os << "[";
    for ( auto i = ts.begin(), ie = ts.end(); i != ie; ++i )
    {
      if ( i != ts.begin() )
        os << ",";
      Json<_T>::json(os, *i);
    }
    os << "]";
  }
};

template <typename _T1, typename _T2>
struct Json<std::map<_T1, _T2>>
{
  static void json(std::ostream& os, const std::map<_T1, _T2>& m)
  {
    os << "[";
    for ( auto i = m.begin(), ie = m.end(); i != ie; ++i )
    {
      if ( i != m.begin() )
        os << ",";
      Json<std::pair<_T1, _T2>>::json(os, *i);
    }
    os << "]";
  }
};

template <typename _T1, typename _T2>
struct Json<std::pair<_T1, _T2>>
{
  static void json(std::ostream& os, const std::pair<_T1, _T2>& p)
  {
    os << "{\"first\":";
    Json<_T1>::json(os, p.first);
    os << ",\"second\":";
    Json<_T2>::json(os, p.second);
    os << "}";
  }
};

template <typename _T>
struct Json<std::set<_T>>
{
  static void json(std::ostream& os, const std::set<_T>& ts)
  {
    os << "[";
    for ( auto i = ts.begin(), ie = ts.end(); i != ie; ++i )
    {
      if ( i != ts.begin() )
        os << ",";
      Json<_T>::json(os, *i);
    }
    os << "]";
  }
};

template <typename _T>
struct Json<std::vector<_T>>
{
  static void json(std::ostream& os, const std::vector<_T>& ts)
  {
    os << "[";
    for ( auto i = ts.begin(), ie = ts.end(); i != ie; ++i )
    {
      if ( i != ts.begin() )
        os << ",";
      Json<_T>::json(os, *i);
    }
    os << "]";
  }
};

template <typename _T>
void json(std::ostream& os, const _T& t)
{
  Json<_T>::json(os, t);
}

}

#endif

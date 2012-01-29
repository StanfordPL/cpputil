#ifndef SERIAL_STREAM_H
#define SERIAL_STREAM_H

#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "delegatestream.h"

namespace cpputil
{

template <typename _Char, typename _Traits>
class basic_oserialstream : public basic_odelegatestream<_Char, _Traits>
{
  public:
    basic_oserialstream(std::ostream& os, char quote = '"') : 
      basic_odelegatestream<_Char, _Traits>(os),
      quote_(quote) 
    {
      // Does nothing.
    }

    void quote() { *this << quote_; }

  private:
    const char quote_;
};

typedef basic_oserialstream<char, std::char_traits<char>> oserialstream;
typedef basic_oserialstream<wchar_t, std::char_traits<wchar_t>> woserialstream;

template <typename _Char, typename _Traits, typename _T>
struct serializer
{
  static void serialize(basic_oserialstream<_Char, _Traits>& os, const _T& t)
  {
    os << t;
  }
};

template <typename _Char, typename _Traits>
struct serializer<_Char, _Traits, const char*>
{
  static void serialize(basic_oserialstream<_Char, _Traits>& os, const char* s)
  {
    os.quote();
    for ( unsigned int i = 0, ie = strlen(s); i < ie; ++i )
      os << s[i];
    os.quote();
  }
};

template <typename _Char, typename _Traits, typename _C, typename _T>
struct serializer<_Char, _Traits, std::basic_string<_C, _T>>
{
  static void serialize(basic_oserialstream<_Char, _Traits>& os, const std::basic_string<_C, _T> s)
  {
    serializer<_Char, _Traits, const char*>::serialize(os, s.c_str());
  }
};

template <typename _Char, typename _Traits, typename _T>
struct serializer<_Char, _Traits, std::deque<_T>>
{
  static void serialize(basic_oserialstream<_Char, _Traits>& os, const std::deque<_T>& ts)
  {
    os << ts.size() << ' ';
    for ( auto t : ts )
    {
      serializer<_Char, _Traits, _T>::serialize(os, t);
      os << ' ';
    }
  }
};

template <typename _Char, typename _Traits, typename _T>
struct serializer<_Char, _Traits, std::list<_T>>
{
  static void serialize(basic_oserialstream<_Char, _Traits>& os, const std::list<_T>& ts)
  {
    os << ts.size() << ' ';
    for ( auto t : ts )
    {
      serializer<_Char, _Traits, _T>::serialize(os, t);
      os << ' ';
    }
  }
};

template <typename _Char, typename _Traits, typename _T1, typename _T2>
struct serializer<_Char, _Traits, std::map<_T1, _T2>>
{
  static void serialize(basic_oserialstream<_Char, _Traits>& os, const std::map<_T1, _T2>& m)
  {
    os << m.size() << ' ';
    for ( auto p : m )
    {
      serializer<_Char, _Traits, std::pair<_T1, _T2>>::serialize(os, p);
      os << ' ';
    }
  }
};

template <typename _Char, typename _Traits, typename _T1, typename _T2>
struct serializer<_Char, _Traits, std::pair<_T1, _T2>>
{
  static void serialize(basic_oserialstream<_Char, _Traits>& os, const std::pair<_T1, _T2>& p)
  {
    serializer<_Char, _Traits, _T1>::serialize(os, p.first);
    os << ' ';
    serializer<_Char, _Traits, _T2>::serialize(os, p.second);
  }
};

template <typename _Char, typename _Traits, typename _T>
struct serializer<_Char, _Traits, std::set<_T>>
{
  static void serialize(basic_oserialstream<_Char, _Traits>& os, const std::set<_T>& ts)
  {
    os << ts.size() << ' ';
    for ( auto t : ts )
    {
      serializer<_Char, _Traits, _T>::serialize(os, t);
      os << ' ';
    }
  }
};

template <typename _Char, typename _Traits, typename _T>
struct serializer<_Char, _Traits, std::vector<_T>>
{
  static void serialize(basic_oserialstream<_Char, _Traits>& os, const std::vector<_T>& ts)
  {
    os << ts.size() << ' ';
    for ( auto t : ts )
    {
      serializer<_Char, _Traits, _T>::serialize(os, t);
      os << ' ';
    }
  }
};

template <typename _Char, typename _Traits, typename _T>
basic_oserialstream<_Char, _Traits>& operator<<(basic_oserialstream<_Char, _Traits>& os, const _T& t)
{
  serializer<_Char, _Traits, _T>::serialize(os, t);
  return os;
}

}

#endif

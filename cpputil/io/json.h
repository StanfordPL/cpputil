#ifndef CPPUTIL_IO_JSON_H
#define CPPUTIL_IO_JSON_H

#include <iostream>
#include <string>
#include <type_traits>

#include "cpputil/traits/traits.h"

namespace cpputil
{

template <typename T> 
struct requires_quotes : public std::false_type {};

template <>
struct requires_quotes<char> : public std::true_type {};
template <>
struct requires_quotes<wchar_t> : public std::true_type {};
template <typename Ch, typename Tr>
struct requires_quotes<std::basic_string<Ch, Tr>> : public std::true_type {};



template <typename Ch, typename Tr, typename T, typename Enable = void>
class basic_jsonwriter;

template <typename Ch, typename Tr, typename T>
class basic_jsonwriter<Ch, Tr, T, typename std::enable_if<std::is_arithmetic<T>::value && !std::is_same<T, char>::value>::type>
{
  public:
    basic_jsonwriter(const T t) : t_(t) {}
    void operator()(std::basic_ostream<Ch, Tr>& os) const
    {
      os << t_;
    }

  private:
    const T t_;
};

template <typename Ch, typename Tr>
class basic_jsonwriter<Ch, Tr, bool>
{
  public:
    basic_jsonwriter(const bool b) : b_(b) {}
    void operator()(std::basic_ostream<Ch, Tr>& os) const
    {
      os << b_ ? "true" : "false";
    }

  private:
    const bool b_;
};

template <typename Ch, typename Tr, typename T>
class basic_jsonwriter<Ch, Tr, T, typename std::enable_if<requires_quotes<T>::value>::type>
{
  public:
    basic_jsonwriter(const T& t) : t_(t) {}
    void operator()(std::basic_ostream<Ch, Tr>& os) const
    {
      os << "\"" << t_ << "\"";
    }

  private:
    const T& t_;
};

template <typename Ch, typename Tr, typename T1, typename T2>
class basic_jsonwriter<Ch, Tr, std::pair<T1, T2>>
{
  public:
    basic_jsonwriter(const std::pair<T1, T2>& p) : p_(p) {}
    void operator()(std::basic_ostream<Ch, Tr>& os) const
    {
      os << "{\"first\":"
         << basic_jsonwriter<Ch, Tr, T1>(p_.first)
         << ",\"second\":"
         << basic_jsonwriter<Ch, Tr, T2>(p_.second)
         << "}";
    }

  private:
    const std::pair<T1, T2>& p_;
};

template <typename Ch, typename Tr, typename T>
class basic_jsonwriter<Ch, Tr, T, typename std::enable_if<is_stl_container<T>::value>::type>
{
  public:
    basic_jsonwriter(const T& t) : t_(t) {}
    void operator()(std::basic_ostream<Ch, Tr>& os) const
    {
      os << "[";
      for ( auto i = t_.begin(), ie = t_.end(); i != ie; ++i )
      {
        if ( i != t_.begin() )
          os << ",";
        os << basic_jsonwriter<Ch, Tr, typename T::value_type>(*i);
      } 
      os << "]";
    }

  private:
    const T& t_;
};

template <typename Ch, typename Tr, typename T>
std::ostream& operator<<(std::basic_ostream<Ch, Tr>& os, const basic_jsonwriter<Ch, Tr, T>& w)
{
  w(os);
  return os;
}

template <typename T>
inline basic_jsonwriter<char, std::char_traits<char>, T> jsonwriter(const T& t)
{
  return basic_jsonwriter<char, std::char_traits<char>, T>(t);
}

template <typename T>
inline basic_jsonwriter<wchar_t, std::char_traits<wchar_t>, T> wjsonwriter(const T& t)
{
  return basic_jsonwriter<wchar_t, std::char_traits<wchar_t>, T>(t);
}

}

#endif

#ifndef CPPUTIL_IO_SERIALIZE_H
#define CPPUTIL_IO_SERIALIZE_H

#include <iostream>
#include <type_traits>

#include <stddef.h>

#include "traits/traits.h"

namespace cpputil
{

template <typename Ch, typename Tr, typename T, typename Enable = void>
class basic_serialwriter;

template <typename Ch, typename Tr, typename T>
class basic_serialwriter<Ch, Tr, T, typename std::enable_if<std::is_scalar<typename std::remove_const<T>::type>::value>::type>
{
  public:
    basic_serialwriter(const T t) : t_(t) {}
    void operator()(std::basic_ostream<Ch, Tr>& os) const 
    { 
      os << t_; 
    }

  private:
    const T t_;  
};

template <typename Ch1, typename Tr1, typename Ch2, typename Tr2>
class basic_serialwriter<Ch1, Tr1, std::basic_string<Ch2, Tr2>>
{
  public:
    basic_serialwriter(const std::basic_string<Ch2, Tr2>& s) : s_(s) {}
    void operator()(std::basic_ostream<Ch1, Tr1>& os) const 
    { 
      os << "\"" << s_ << "\""; 
    }

  private:  
    const std::basic_string<Ch2, Tr2>& s_;  
};

template <typename Ch, typename Tr, typename T>
class basic_serialwriter<Ch, Tr, T, typename std::enable_if<is_stl_container<typename std::remove_const<T>::type>::value>::type>
{
  public:
    basic_serialwriter(const T& t) : t_(t) {}
    void operator()(std::basic_ostream<Ch, Tr>& os) const 
    { 
      os << t_.size();

      if ( t_.empty() )
        os << " ";

      for ( auto i = t_.begin(), ie = t_.end(); i != ie; ++i )
        os << " " << basic_serialwriter<Ch, Tr, typename T::value_type>(*i);
    }

  private: 
    const T& t_;  
};

template <typename Ch, typename Tr, typename T1, typename T2>
class basic_serialwriter<Ch, Tr, std::pair<T1, T2>>
{
  public:
    basic_serialwriter(const std::pair<T1, T2>& p) : p_(p) {}
    void operator()(std::basic_ostream<Ch, Tr>& os) const 
    {
      os << basic_serialwriter<Ch, Tr, T1>(p_.first)
         << " "
         << basic_serialwriter<Ch, Tr, T2>(p_.second);
    }

  private:  
    const std::pair<T1, T2>& p_;  
};

template <typename Ch, typename Tr, typename T>
std::ostream& operator<<(std::basic_ostream<Ch, Tr>& os, const basic_serialwriter<Ch, Tr, T>& w)
{
  w(os);
  return os;
}

template <typename T>
basic_serialwriter<char, std::char_traits<char>, T> serialwriter(const T& t)
{
  return basic_serialwriter<char, std::char_traits<char>, T>(t);
}



template <typename Ch, typename Tr, typename T, typename Enable = void>
class basic_serialreader;

template <typename Ch, typename Tr, typename T>
class basic_serialreader<Ch, Tr, T, typename std::enable_if<std::is_scalar<T>::value>::type>
{
  public:
    basic_serialreader(T& t) : t_(t) {}
    void operator()(std::basic_istream<Ch, Tr>& is) const
    { 
      is >> t_; 
    }

  private:
    T& t_;  
};

template <typename Ch1, typename Tr1, typename Ch2, typename Tr2>
class basic_serialreader<Ch1, Tr1, std::basic_string<Ch2, Tr2>>
{
  public:
    basic_serialreader(std::basic_string<Ch2, Tr2>& s) : s_(s) {}
    void operator()(std::basic_istream<Ch1, Tr1>& is) const
    { 
      getline(is, s_, '"');
      getline(is, s_, '"');
    }

  private:  
    std::basic_string<Ch2, Tr2>& s_;  
};

template <typename Ch, typename Tr, typename T>
class basic_serialreader<Ch, Tr, T, typename std::enable_if<is_stl_map<T>::value>::type>
{
  public:
    basic_serialreader(T& t) : t_(t) {}
    void operator()(std::basic_istream<Ch, Tr>& is) const
    { 
      t_.clear();

      size_t size;
      is >> size;

      for ( size_t i = 0; i < size; ++i )
      {
        typename T::key_type k;
        typename T::mapped_type v;

        is >> basic_serialreader<Ch, Tr, typename T::key_type>(k)
           >> basic_serialreader<Ch, Tr, typename T::mapped_type>(v);

        t_.insert(std::make_pair(k,v));
      }
    }

  private: 
    T& t_;  
};

template <typename Ch, typename Tr, typename T>
class basic_serialreader<Ch, Tr, T, typename std::enable_if<is_stl_set<T>::value>::type>
{
  public:
    basic_serialreader(T& t) : t_(t) {}
    void operator()(std::basic_istream<Ch, Tr>& is) const
    { 
      t_.clear();

      size_t size;
      is >> size;

      for ( size_t i = 0; i < size; ++i )
      {
        typename T::value_type v;
        is >> basic_serialreader<Ch, Tr, typename T::value_type>(v);
        t_.insert(v);
      }
    }

  private: 
    T& t_;  
};

template <typename Ch, typename Tr, typename T>
class basic_serialreader<Ch, Tr, T, typename std::enable_if<is_stl_sequence<T>::value>::type>
{
  public:
    basic_serialreader(T& t) : t_(t) {}
    void operator()(std::basic_istream<Ch, Tr>& is) const
    { 
      t_.clear();

      size_t size;
      is >> size;

      for ( size_t i = 0; i < size; ++i )
      {
        typename T::value_type v;
        is >> basic_serialreader<Ch, Tr, typename T::value_type>(v);
        t_.emplace_back(v);
      } 
    }

  private: 
    T& t_;  
};

template <typename Ch, typename Tr, typename T1, typename T2>
class basic_serialreader<Ch, Tr, std::pair<T1, T2>>
{
  public:
    basic_serialreader(std::pair<T1, T2>& p) : p_(p) {}
    void operator()(std::basic_istream<Ch, Tr>& is) const
    {
      is >> basic_serialreader<Ch, Tr, T1>(p_.first)
         >> basic_serialreader<Ch, Tr, T2>(p_.second);
    }

  private:  
    std::pair<T1, T2>& p_;  
};

template <typename Ch, typename Tr, typename T>
std::istream& operator>>(std::basic_istream<Ch, Tr>& is, const basic_serialreader<Ch, Tr, T>& r)
{
  r(is);
  return is;
}

template <typename T>
basic_serialreader<char, std::char_traits<char>, T> serialreader(T& t)
{
  return basic_serialreader<char, std::char_traits<char>, T>(t);
}

}

#endif

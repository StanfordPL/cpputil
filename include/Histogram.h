#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <iostream>
#include <map>

#include "serialize.h"

namespace cpputil
{

template <typename _T, typename _Associative = std::map<const _T, unsigned int>>
class Histogram
{
  public:

    // Member types
    typedef          _T                           value_type;
    typedef          const _T&                    const_reference;
    typedef          unsigned int                 mass_type;
    typedef typename _Associative::const_iterator const_iterator;
    typedef typename _Associative::size_type      size_type;

    // Iterators
    const_iterator begin() const { return histogram_.begin(); }
    const_iterator cbegin() const { return begin(); }
    const_iterator end() const { return histogram_.end(); }
    const_iterator cend() const { return end(); }

    // Capacity
    size_type size() const { return histogram_.size(); }

    // Modifiers
    void clear() { histogram_.clear(); }
    void insert(const_reference val, mass_type mass)
    {
      auto itr = histogram_.find(val);
      if ( itr == histogram_.end() )
        histogram_[val] = mass;
      else
        itr->second += mass;
    }
    Histogram& operator+=(const Histogram& rhs)
    {
      for ( auto itr : rhs )
        insert(itr.first, itr.second);
      return *this;
    }
    Histogram operator+(const Histogram& rhs)
    {
      Histogram h = *this;
      h += rhs;
      return h;
    }

  private:
    _Associative histogram_;
};

template <typename _T>
struct Serializer<Histogram<_T>>
{
  static void serialize(std::ostream& os, const Histogram<_T>& h, char delim = '"')
  {
    os << h.size() << " ";
    for ( auto itr : h )
    {
      Serializer<typename Histogram<_T>::value_type>::serialize(os, itr.first, delim);
      os << " ";
      Serializer<typename Histogram<_T>::mass_type>::serialize(os, itr.second, delim);
      os << " ";
    }
  }
};

template <typename _T>
struct Deserializer<Histogram<_T>>
{
  static void deserialize(std::istream& is, Histogram<_T>& h, char delim = '"')
  {
    h.clear();

    typename Histogram<_T>::size_type size;
    is >> size;

    typename Histogram<_T>::value_type val;
    typename Histogram<_T>::mass_type mass;
    for ( auto i = 0; i < size; ++i )
    {
      Deserializer<typename Histogram<_T>::value_type>::deserialize(is, val, delim);
      Deserializer<typename Histogram<_T>::mass_type>::deserialize(is, mass, delim);

      h.insert(val, mass);
    }
  }
};

}

#endif

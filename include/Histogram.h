#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <iostream>
#include <map>

#include "serialize.h"

namespace cpputil
{

template <typename _T, 
          typename _Mass = unsigned int,
          typename _Associative = std::map<_T, _Mass>>
class Histogram
{
  // Friends
  friend class Serializer<Histogram>;
  friend class Deserializer<Histogram>;

  public:

    // Member types
    typedef          _T                                   value_type;
    typedef          const _T&                            const_reference;
    typedef          _Mass                                mass_type;
    typedef typename _Associative::const_iterator         const_iterator;
    typedef typename _Associative::const_reverse_iterator const_reverse_iterator;
    typedef typename _Associative::size_type              size_type;

    // Iterators
    const_iterator begin() const { return histogram_.begin(); }
    const_iterator cbegin() const { return begin(); }
    const_iterator end() const { return histogram_.end(); }
    const_iterator cend() const { return end(); }

    const_reverse_iterator rbegin() const { return histogram_.rbegin(); }
    const_reverse_iterator crbegin() const { return rbegin(); }
    const_reverse_iterator rend() const { return histogram_.rend(); }
    const_reverse_iterator crend() const { return rend(); }

    // Capacity
    bool empty() const { return histogram_.empty(); }
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
    void swap(Histogram& rhs) { histogram_.swap(rhs.histogram_); }
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

template <typename _T, typename _Mass, typename _Associative>
struct Serializer<Histogram<_T, _Mass, _Associative>>
{
  static void serialize(std::ostream& os, const Histogram<_T, _Mass, _Associative>& h, char delim = '"')
  {
    Serializer<_Associative>::serialize(os, h.histogram_, delim);
  }
};

template <typename _T, typename _Mass, typename _Associative>
struct Deserializer<Histogram<_T, _Mass, _Associative>>
{
  static void deserialize(std::istream& is, Histogram<_T, _Mass, _Associative>& h, char delim = '"')
  {
    Deserializer<_Associative>::deserialize(is, h.histogram_, delim);    
  }
};

}

#endif

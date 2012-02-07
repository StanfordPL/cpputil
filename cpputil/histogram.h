#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <iostream>
#include <map>

#include "cpputil/maputil.h"
#include "cpputil/serialize.h"

namespace cpputil
{

template <typename _T, 
          typename _Mass = unsigned int,
          typename _Associative = std::map<_T, _Mass>>
class histogram
{
  // Friends
  friend class Serializer<histogram>;
  friend class Deserializer<histogram>;

  public:

    // Member types
    typedef          _T                                       value_type;
    typedef          const _T&                                const_reference;
    typedef          _Mass                                    mass_type;
    typedef typename _Associative::const_iterator             const_iterator;
    typedef typename _Associative::const_reverse_iterator     const_reverse_iterator;
    typedef          const_key_iterator<_Associative>         const_value_iterator;
    typedef          const_reverse_key_iterator<_Associative> const_reverse_value_iterator;
    typedef typename _Associative::size_type                  size_type;

    // Iterators
    const_iterator begin() const { return histogram_.begin(); }
    const_iterator cbegin() const { return begin(); }
    const_iterator end() const { return histogram_.end(); }
    const_iterator cend() const { return end(); }

    const_reverse_iterator rbegin() const { return histogram_.rbegin(); }
    const_reverse_iterator crbegin() const { return rbegin(); }
    const_reverse_iterator rend() const { return histogram_.rend(); }
    const_reverse_iterator crend() const { return rend(); }

    const_value_iterator value_begin() const { return const_value_iterator(histogram_.begin()); }
    const_value_iterator value_cbegin() const { return value_begin(); }
    const_value_iterator value_end() const { return const_value_iterator(histogram_.end()); }
    const_value_iterator value_cend() const { return value_end(); }

    const_reverse_value_iterator value_rbegin() const { return const_reverse_value_iterator(histogram_.rbegin()); }
    const_reverse_value_iterator value_crbegin() const { return value_rbegin(); }
    const_reverse_value_iterator value_rend() const { return const_reverse_value_iterator(histogram_.rend()); }
    const_reverse_value_iterator value_crend() const { return value_rend(); }

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
    void swap(histogram& rhs) { histogram_.swap(rhs.histogram_); }
    histogram& operator+=(const histogram& rhs)
    {
      for ( auto itr : rhs )
        insert(itr.first, itr.second);
      return *this;
    }
    histogram operator+(const histogram& rhs)
    {
      histogram h = *this;
      h += rhs;
      return h;
    }

  private:
    _Associative histogram_;
};

template <typename _T, typename _Mass, typename _Associative>
struct Serializer<histogram<_T, _Mass, _Associative>>
{
  static void serialize(std::ostream& os, const histogram<_T, _Mass, _Associative>& h, char delim = '"')
  {
    Serializer<_Associative>::serialize(os, h.histogram_, delim);
  }
};

template <typename _T, typename _Mass, typename _Associative>
struct Deserializer<histogram<_T, _Mass, _Associative>>
{
  static void deserialize(std::istream& is, histogram<_T, _Mass, _Associative>& h, char delim = '"')
  {
    Deserializer<_Associative>::deserialize(is, h.histogram_, delim);    
  }
};

}

#endif

#ifndef RANDOMVAR_H
#define RANDOMVAR_H

#include <cassert>
#include <cstdlib>
#include <iostream>

#include "cpputil/histogram.h"
#include "cpputil/serialize.h"

namespace cpputil
{

template <typename _T, 
          typename _Histogram = Histogram<_T>>
class randomvar
{
  // Friends
  friend class Serializer<randomvar>;
  friend class Deserializer<randomvar>;

  public:

    // Member types
    typedef typename _Histogram::value_type      value_type;
    typedef typename _Histogram::const_reference const_reference;
    typedef typename _Histogram::mass_type       mass_type;

    // Constructors
    randomvar() : mass_(0) {}

    // Element access
    const_reference sample() const
    {
      assert(mass_ > 0 && "Cannot sample from a zero mass distribution!");

      mass_type p = rand() % mass_;
      for ( auto itr : vals_ )
        if ( p < itr.second )
          return itr.first;
        else
          p -= itr.second;

      assert(false && "Control should never reach here!");
      return T();
    }

    // Modifiers
    void clear()
    {
      mass_ = 0;
      vals_.clear();
    }
    void insert(const_reference val, mass_type mass)
    {
      mass_ += mass;
      vals_.insert(val, mass);
    }
    void swap(randomvar& rhs)
    {
      swap(mass_, rhs.mass);
      vals_.swap(rhs.vals_);
    }

  private:
    mass_type mass_;
    Histogram_ vals_;
};

template <typename _T, typename _Histogram>
struct Serializer<randomvar<_T, _Histogram>>
{
  static void serialize(std::ostream& os, const randomvar<_T, _Histogram>& rv, char delim = '"')
  {
    Serializer<randomvar<_T, _Histogram>::mass_type>::serialize(os, rv.mass_, delim);
    Serializer<Histogram_>::serialize(os, rv.vals_, delim);
  }
};

template <typename _T, typename _Histogram>
struct Deserializer<randomvar<_T, _Histogram>>
{
  static void deserialize(std::istream& is, randomvar<_T, _Histogram>& rv, char delim = '"')
  {
    Deserializer<typename randomvar<_T, _Histogram>::mass_type>::deserialize(is, rv.mass_, delim);
    Deserializer<Histogram_>::deserialize(is, rv.vals_, delim);
  }
};

}

#endif

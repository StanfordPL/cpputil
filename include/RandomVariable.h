#ifndef RANDOM_VARIABLE_H
#define RANDOM_VARIABLE_H

#include <cassert>
#include <cstdlib>
#include <iostream>

#include "Histogram.h"
#include "serialize.h"

namespace cpputil
{

template <typename _T, typename _Associative = std::map<_T, unsigned int>>
class RandomVariable
{
  // Friends
  friend class Serializer<RandomVariable>;
  friend class Deserializer<RandomVariable>;

  public:

    // Member types
    typedef typename Histogram<_T, _Associative>::value_type      value_type;
    typedef typename Histogram<_T, _Associative>::const_reference const_reference;
    typedef typename Histogram<_T, _Associative>::mass_type       mass_type;

    // Constructors
    RandomVariable() : mass_(0) {}

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
      vals_.count(val, mass);
    }

  private:
    mass_type mass_;
    Histogram<_T, _Associative> vals_;
};

template <typename _T, typename _Associative>
struct Serializer<RandomVariable<_T, _Associative>>
{
  static void serialize(std::ostream& os, const RandomVariable<_T, _Associative>& rv, char delim = '"')
  {
    Serializer<typename RandomVariable<_T, _Associative>::mass_type>::serialize(os, rv.mass_, delim);
    Serializer<Histogram<_T, _Associative>>::serialize(os, rv.vals_, delim);
  }
};

template <typename _T, typename _Associative>
struct Deserializer<RandomVariable<_T, _Associative>>
{
  static void deserialize(std::istream& is, RandomVariable<_T, _Associative>& rv, char delim = '"')
  {
    Deserializer<typename RandomVariable<_T, _Associative>::mass_type>::deserialize(is, rv.mass_, delim);
    Deserializer<Histogram<_T, _Associative>>::deserialize(is, rv.vals_, delim);
  }
};

}

#endif

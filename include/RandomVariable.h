#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <cassert>
#include <cstdlib>

#include "Histogram.h"

namespace cpputil
{

template <typename _T, typename _Associative = std::map<const _T, unsigned int>>
class RandomVariable
{
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

}

#endif

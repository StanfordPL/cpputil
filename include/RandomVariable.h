#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <cassert>
#include <cstdlib>
#include <utility>

namespace cpputil
{

template <typename _T, typename _Sequence = std::deque<const T> >
class RandomVariable
{
  public:
    typedef unsigned int mass_type;
    typedef _T           value_type;
    typedef const _T&    const_reference;

    RandomVariable() : 
      mass_(0) 
    {
      // Does nothing.
    }

    void clear()
    {
      mass_ = 0;
      vals_.clear();
    }

    void insert(mass_type mass, const_reference val)
    {
      assert(find(vals_.begin(), vals_.end(), val) == vals_.end() && "Cannot insert duplicate value!");
      assert(mass > 0 && "Unable to insert element with zero mass!");

      mass_ += mass;
      vals_.push_back(std::pair<mass_type, T>(mass_, val));
    }

    const_reference sample() const
    {
      assert(mass_ > 0 && "Cannot sample from a zero mass distribution!");

      mass_type p = rand() % mass_;
      for ( auto i = vals_.begin(), ie = vals_.end(); i != ie; ++i )
        if ( p < i->first )
          return i->second;

      assert(false && "Control should never reach here!");
      return T();
    }

  private:
    mass_type mass_;
    _Sequence<std::pair<mass_type, _T> > vals_;
};

}

#endif

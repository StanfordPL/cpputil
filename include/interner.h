#ifndef INTERNER_H
#define INTERNER_H

#include <iostream>
#include <set>

#include "serialize.h"

namespace cpputil
{

template <typename _T,
          typename _Set = std::set<_T>>
class Interner
{
  // Friends:
  friend class Serializer<Interner>;
  friend class Deserializer<Interner>;

  public:
   
    // Member types
    typedef          _T                           value_type;
    typedef          const _T&                    const_reference; 
    typedef typename _Set::size_type              size_type;
    typedef typename _Set::const_iterator         const_iterator;
    typedef typename _Set::const_reverse_iterator const_reverse_iterator;

    // Element access
    const_reference intern(const_reference t)
    {
      auto res = vals_.insert(t);
      return *(res.first);
    }

    // Iterators
    const_iterator begin() const { return vals_.begin(); }
    const_iterator cbegin() const { return begin(); }
    const_iterator end() const { return vals_.end(); }
    const_iterator cend() const { return end(); }

    const_reverse_iterator rbegin() const { return vals_.rbegin(); }
    const_reverse_iterator crbegin() const { return rbegin(); }
    const_reverse_iterator rend() const { return vals_.rend(); }
    const_reverse_iterator crend() const { return rend(); }

    // Capacity
    bool empty() const { return vals_.empty(); }
    size_type size() const { return vals_.size(); }

    // Modifiers
    void clear() { vals_.clear(); }
    void swap(Interner& rhs) { vals_.swap(rhs.vals_); }

  private:
    _Set vals_;
};

template <typename _T, typename _Set>
struct Serializer<Interner<_T, _Set>>
{
  static void serialize(std::ostream& os, const Interner<_T, _Set>& i, char delim = ' ')
  {
    Serializer<_Set>::serialize(os, i.vals_, delim);
  }
};

template <typename _T, typename _Set>
struct Deserializer<Interner<_T, _Set>>
{
  static void deserialize(std::istream& is, Interner<_T, _Set>& i, char delim = ' ')
  {
    Deserializer<_Set>::deserialize(is, i.vals_, delim);
  }
};

}

#endif

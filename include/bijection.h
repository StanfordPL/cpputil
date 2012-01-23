#ifndef BIJECTION_H
#define BIJECTION_H

#include <cassert>
#include <iostream>
#include <map>

#include "maputil.h"
#include "serialize.h"

namespace cpputil
{

template <typename _Domain, typename _Range, 
          typename _Associative1 = std::map<_Domain, _Range>,
          typename _Associative2 = std::map<_Range, _Domain>>
class bijection
{
  // Friends
  friend class Serializer<bijection>;
  friend class Deserializer<bijection>;

  public:

    // Member types
    typedef          _Domain                                   domain_type;
    typedef          const _Domain&                            const_domain_reference;
    typedef          const_key_iterator<_Associative1>         const_domain_iterator;
    typedef          const_reverse_key_iterator<_Associative1> const_reverse_domain_iterator;
    typedef          _Range                                    range_type;
    typedef          const _Range&                             const_range_reference;
    typedef          const_key_iterator<_Associative2>         const_range_iterator;
    typedef          const_reverse_key_iterator<_Associative2> const_reverse_range_iterator;
    typedef typename _Associative1::const_iterator             const_iterator;
    typedef typename _Associative1::const_reverse_iterator     const_reverse_iterator;
    typedef typename _Associative1::size_type                  size_type;

    // Iterators
    const_iterator begin() const { return domain_.begin(); }
    const_iterator cbegin() const { return begin(); }
    const_iterator end() const { return domain_.end(); }
    const_iterator cend() const { return end(); }

    const_reverse_iterator rbegin() const { return domain_.rbegin(); }
    const_reverse_iterator crbegin() const { return rbegin(); }
    const_reverse_iterator rend() const { return domain_.rend(); }
    const_reverse_iterator crend() const { return rend(); }

    const_domain_iterator domain_begin() const { return const_domain_iterator(domain_.begin()); }
    const_domain_iterator domain_cbegin() const { return domain_begin(); }
    const_domain_iterator domain_end() const { return const_domain_iterator(domain_.end()); }
    const_domain_iterator domain_cend() const { return domain_end(); }

    const_reverse_domain_iterator domain_rbegin() const { return const_reverse_domain_iterator(domain_.rbegin()); }
    const_reverse_domain_iterator domain_crbegin() const { return domain_crbegin(); }
    const_reverse_domain_iterator domain_rend() const { return const_reverse_domain_iterator(domain_.rend()); }
    const_reverse_domain_iterator domain_crend() const { return domain_crend(); }

    const_range_iterator range_begin() const { return const_range_iterator(range_.begin()); }
    const_range_iterator range_cbegin() const { return range_cbegin(); }
    const_range_iterator range_end() const { return const_range_iterator(range_.end()); }
    const_range_iterator range_cend() const { return range_cend(); }

    const_reverse_range_iterator range_rbegin() const { return const_reverse_range_iterator(range_.rbegin()); }
    const_reverse_range_iterator range_crbegin() const { return range_crbegin(); }
    const_reverse_range_iterator range_rend() const { return const_reverse_range_iterator(range_.rend()); }
    const_reverse_range_iterator range_crend() const { return range_crend(); }

    // Capacity
    bool empty() const { return domain_.empty(); }
    size_type size() const { return domain_.size(); }

    // Modifiers
    void clear()
    {
      domain_.clear();
      range_.clear();
    }
    std::pair<const_iterator, bool> insert(const_domain_reference d, const_range_reference r)
    {
      auto itr = domain_.find(d);
      if ( itr == domain_.end() )
      {
        assert(range_.find(r) == range_.end() && "Duplicate range element!");
        range_[r] = d;
        return domain_.insert(std::make_pair(d, r));
      }
      else
      {
        assert(itr->second == r && "Inconsistent range element!");
        return std::make_pair(itr, false);
      }
    } 
    void domain_erase(const_domain_reference d)
    {
      assert(domain_.find(d) != domain_.end() && "Unrecognized domain element!");
      
      auto itr = domain_.find(d);
      range_.erase(itr->second);
      domain_.erase(itr);
    }
    void range_erase(const_range_reference r)
    {
      assert(range_.find(r) != range_.end() && "Unrecognized range element!");

      auto itr = range_.find(r);
      domain_.erase(itr->second);
      range_.erase(itr);
    }
    void swap(bijection& rhs)
    {
      domain_.swap(rhs.domain_);
      range_.swap(rhs.domain_);
    }

    // Lookup
    const_domain_iterator domain_find(const_domain_reference d) const { return const_domain_iterator(domain_.find(d)); }
    const_range_iterator range_find(const_range_reference r) const { return const_range_iterator(range_.find(r)); }

    const_range_reference domain_assert_at(const_domain_reference d) const { return assert_at(domain_, d); }
    const_domain_reference range_assert_at(const_range_reference r) const { return assert_at(range_, r); }

  private:
    _Associative1 domain_;
    _Associative2 range_;
};  

template <typename _Domain, typename _Range, typename _Associative1, typename _Associative2>
struct Serializer<bijection<_Domain, _Range, _Associative1, _Associative2>>
{
  static void serialize(std::ostream& os, const bijection<_Domain, _Range, _Associative1, _Associative2>& b, char delim = '"')
  {
    Serializer<_Associative1>::serialize(os, b.domain_, delim);
  }
};

template <typename _Domain, typename _Range, typename _Associative1, typename _Associative2>
struct Deserializer<bijection<_Domain, _Range, _Associative1, _Associative2>>
{
  static void deserialize(std::istream& is, bijection<_Domain, _Range, _Associative1, _Associative2>& b, char delim = '"')
  {
    Deserializer<_Associative1>::deserialize(is, b.domain_, delim);

    b.range_.clear();
    for ( auto itr : b.domain_ )
      b.range_[itr.second] = itr.first;
  }
};

}

#endif

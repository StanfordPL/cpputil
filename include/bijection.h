#ifndef BIJECTION_H
#define BIJECTION_H

#include <cassert>
#include <map>

#include "maputil.h"

namespace cpputil
{

template <typename _Domain, typename _Range, typename _Associative1 = std::map<_Domain, const _Range*>, typename _Associative2 = std::map<_Range, const _Domain*> >
class bijection
{
  public:

    // Member types
    typedef          const _Domain&                            const_domain_reference;
    typedef          const_key_iterator<_Associative1>         const_domain_iterator;
    typedef          const_reverse_key_iterator<_Associative1> const_reverse_domain_iterator;
    typedef          const _Range&                             const_range_reference;
    typedef          const_key_iterator<_Associative2>         const_range_iterator;
    typedef          const_reverse_key_iterator<_Associative2> const_reverse_range_iterator;
    typedef typename _Associative1::size_type                  size_type;

    class const_iterator
    {
      public:
        const_iterator() = delete;
        const_iterator(const typename _Associative1::const_iterator& itr) : itr_(itr) {}

        const_iterator& operator++() 
        { 
          itr_++; 
          return *this;
        }
        std::pair<const _Domain&, const _Range&> operator*() const { return std::make_pair(itr_->first, *itr_->second); }

        bool operator==(const const_iterator& rhs) const { return itr_ == rhs.itr_; }
        bool operator!=(const const_iterator& rhs) const { return !*this == rhs; }

      private:
        typename _Associative1::const_iterator itr_;  
    };

    class const_reverse_iterator
    {
      public:
        const_reverse_iterator() = delete;
        const_reverse_iterator(const typename _Associative1::const_reverse_iterator& itr) : itr_(itr) {}

        const_reverse_iterator& operator++() 
        { 
          itr_++; 
          return *this;
        }
        std::pair<const _Domain&, const _Range&> operator*() const { return std::make_pair(itr_->first, *itr_->second); }

        bool operator==(const const_reverse_iterator& rhs) const { return itr_ == rhs.itr_; }
        bool operator!=(const const_reverse_iterator& rhs) const { return !*this == rhs; }

      private:
        typename _Associative1::const_reverse_iterator itr_;
    };

    // Constructors
    bijection() {}
    bijection(const bijection& rhs)
    {
      clear();
      for ( auto itr : rhs.domainToRange_ )
        insert(itr.first, *itr.second);
    }
    bijection& operator=(bijection rhs)
    {
      swap(rhs);
      return *this;
    }

    // Iterators
    const_iterator begin() const { return const_iterator(domainToRange_.begin()); }
    const_iterator cbegin() const { return begin(); }
    const_iterator end() const { return const_iterator(domainToRange_.end()); }
    const_iterator cend() const { return end(); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(domainToRange_.rbegin()); }
    const_reverse_iterator crbegin() const { return rbegin(); }
    const_reverse_iterator rend() const { return const_reverse_iterator(domainToRange_.rend()); }
    const_reverse_iterator crend() const { return rend(); }

    const_domain_iterator domain_begin() const { return const_domain_iterator(domainToRange_.begin()); }
    const_domain_iterator domain_cbegin() const { return domain_begin(); }
    const_domain_iterator domain_end() const { return const_domain_iterator(domainToRange_.end()); }
    const_domain_iterator domain_cend() const { return domain_end(); }

    const_reverse_domain_iterator domain_rbegin() const { return const_reverse_domain_iterator(domainToRange_.rbegin()); }
    const_reverse_domain_iterator domain_crbegin() const { return domain_crbegin(); }
    const_reverse_domain_iterator domain_rend() const { return const_reverse_domain_iterator(domainToRange_.rend()); }
    const_reverse_domain_iterator domain_crend() const { return domain_crend(); }

    const_range_iterator range_begin() const { return const_range_iterator(rangeToDomain_.begin()); }
    const_range_iterator range_cbegin() const { return range_cbegin(); }
    const_range_iterator range_end() const { return const_range_iterator(rangeToDomain_.end()); }
    const_range_iterator range_cend() const { return range_cend(); }

    const_reverse_range_iterator range_rbegin() const { return const_reverse_range_iterator(rangeToDomain_.rbegin()); }
    const_reverse_range_iterator range_crbegin() const { return range_crbegin(); }
    const_reverse_range_iterator range_rend() const { return const_reverse_range_iterator(rangeToDomain_.rend()); }
    const_reverse_range_iterator range_crend() const { return range_crend(); }

    // Capacity
    bool empty() const { return domainToRange_.empty(); }
    size_type size() const { return domainToRange_.size(); }

    // Modifiers
    void clear()
    {
      domainToRange_.clear();
      rangeToDomain_.clear();
    }
    void insert(const_domain_reference d, const_range_reference r)
    {
      assert(findDomain(d) == cendDomain() && "Duplicate domain element!");
      assert(findRange(r) == cendRange() && "Duplicate range element!");
      
      auto entry1 = typename _Associative1::value_type(d, 0);
      auto entry2 = typename _Associative2::value_type(r, 0);

      auto res1 = domainToRange_.insert(entry1);
      auto res2 = rangeToDomain_.insert(entry2);

      res1.first->second = &res2.first->first;
      res2.first->second = &res1.first->first;
    } 
    void domain_erase(const_domain_reference d)
    {
      rangeToDomain_.erase(*assert_at(domainToRange_, d));
      domainToRange_.erase(d);
    }
    void range_erase(const_range_reference r)
    {
      domainToRange_.erase(*assert_at(rangeToDomain_, r));
      rangeToDomain_.erase(r);
    }
    void swap(bijection& rhs)
    {
      domainToRange_.swap(rhs.domainToRange_);
      rangeToDomain_.swap(rhs.rangeToDomain_);
    }

    // Lookup
    const_iterator domain_find(const_domain_reference d) const { return const_iterator(domainToRange_.find(d)); }
    //const_iterator range_find(const_range_reference r) const { return const_iterator(rangeToDomain_.find(r); }

    const_range_reference domain_assert_at(const_domain_reference d) const { return *assert_at(domainToRange_, d); }
    const_domain_reference range_assert_at(const_range_reference r) const { return *assert_at(rangeToDomain_, r); }

  private:
    _Associative1 domainToRange_;
    _Associative2 rangeToDomain_;
};

}

#endif

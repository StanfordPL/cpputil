#ifndef BIJECTION_H
#define BIJECTION_H

#include <cassert>
#include <map>

namespace cpputil
{

template <typename _Domain, typename _Range, typename _Associative1 = std::map<const _Domain, const _Range*>, typename _Associative2 = std::map<const _Range, const _Domain*> >
class bijection
{
  public:
    typedef _Domain                                        domain_type;
    typedef const _Domain&                                 domain_const_reference;
    typedef typename _Associative1::const_iterator         domain_const_iterator;
    typedef typename _Associative1::const_reverse_iterator domain_const_reverse_iterator;
    typedef typename _Associative1::size_type              size_type;
    typedef _Range                                         range_type;
    typedef const _Range&                                  range_const_reference;
    typedef typename _Associative2::const_iterator         range_const_iterator;
    typedef typename _Associative2::const_reverse_iterator range_const_reverse_iterator;

    bijection()
    {
      // Does nothing.
    }
    bijection(const bijection& rhs)
    {
      clear();
      for ( const typename _Associative1::value_type& i : rhs.domainToRange_ )        
        insert(i.first, *i.second);
    }
    bijection& operator=(bijection rhs)
    {
      swap(rhs);
      return *this;
    }

    domain_const_iterator beginDomain() const { return domainToRange_.begin(); }
    domain_const_iterator cbeginDomain() const { return domainToRange_.cbegin(); }
    domain_const_iterator endDomain() const { return domainToRange_.end(); }
    domain_const_iterator cendDomain() const { return domainToRange_.cend(); }
    domain_const_reverse_iterator rbeginDomain() const { return domainToRange_.rbegin(); }
    domain_const_reverse_iterator crbeginDomain() const { return domainToRange_.crbegin(); }
    domain_const_reverse_iterator rendDomain() const { return domainToRange_.rend(); }
    domain_const_reverse_iterator crendDomain() const { return domainToRange_.crend(); }

    range_const_iterator beginRange() const { return rangeToDomain_.begin(); }
    range_const_iterator cbeginRange() const { return rangeToDomain_.cbegin(); }
    range_const_iterator endRange() const { return rangeToDomain_.end(); }
    range_const_iterator cendRange() const { return rangeToDomain_.cend(); }
    range_const_reverse_iterator rbeginRange() const { return rangeToDomain_.rbegin(); }
    range_const_reverse_iterator crbeginRange() const { return rangeToDomain_.crbegin(); }
    range_const_reverse_iterator rendRange() const { return rangeToDomain_.rend(); }
    range_const_reverse_iterator crendRange() const { return rangeToDomain_.crend(); }

    bool empty() const { return domainToRange_.empty(); }
    size_type size() const { return domainToRange_.size(); }

    void clear()
    {
      domainToRange_.clear();
      rangeToDomain_.clear();
    }
    void insert(domain_const_reference d, range_const_reference r)
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
    void eraseDomain(domain_const_reference d)
    {
      assert(findDomain(d) != cendDomain() && "Unrecognized domain element!");

      rangeToDomain_.erase(*(findDomain(d)->second));
      domainToRange_.erase(d);
    }
    void eraseRange(range_const_reference r)
    {
      assert(findRange(r) != cendRange() && "Unrecognized range element!");

      domainToRange_.erase(*(findRange(r)->second));
      rangeToDomain_.erase(r);
    }
    void swap(bijection& rhs)
    {
      domainToRange_.swap(rhs.domainToRange_);
      rangeToDomain_.swap(rhs.rangeToDomain_);
    }

    domain_const_iterator findDomain(domain_const_reference d) const { return domainToRange_.find(d); }
    range_const_iterator findRange(range_const_reference r) const { return rangeToDomain_.find(r); }

  private:
    _Associative1 domainToRange_;
    _Associative2 rangeToDomain_;
};

}

#endif

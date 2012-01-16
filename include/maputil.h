#ifndef MAP_UTIL_H
#define MAP_UTIL_H

#include <cassert>

namespace cpputil
{

template <typename _Associative>
inline typename _Associative::value_type::second_type& assert_at(_Associative& a, const typename _Associative::value_type::first_type& key)
{
  assert(a.find(key) != a.end() && "Unrecognized key!");
  return a.find(key)->second;
}

template <typename _Associative>
inline const typename _Associative::value_type::second_type& assert_at(const _Associative& a, const typename _Associative::value_type::first_type& key)
{
  assert(a.find(key) != a.end() && "Unrecognized key!");
  return a.find(key)->second;
}

template <typename _Associative>
inline typename _Associative::size_type assert_erase(_Associative& a, const typename _Associative::value_type::first_type& key)
{
  assert(a.find(key) != a.end() && "Unrecognized key!");
  return a.erase(key);
}

template <typename _Associative>
class value_iterator
{
  public:
    value_iterator() = delete;

    value_iterator(const typename _Associative::iterator& itr) : itr_(itr) {}

    void operator++() { itr_++; }
    typename _Associative::mapped_type& operator*() const { return itr_->second; }

    bool operator==(const value_iterator& rhs) { return itr_ == rhs.itr_; }
    bool operator!=(const value_iterator& rhs) { return itr_ != rhs.itr_; }

  private:
    typename _Associative::iterator itr_; 
};

template <typename _Associative>
class const_key_iterator
{
  public:
    const_key_iterator() = delete;

    const_key_iterator(const typename _Associative::const_iterator& itr) : itr_(itr) {}

    void operator++() { itr_++; }
    const typename _Associative::key_type& operator*() const { return itr_->first; }

    bool operator==(const const_key_iterator& rhs) { return itr_ == rhs.itr_; }
    bool operator!=(const const_key_iterator& rhs) { return itr_ != rhs.itr_; }

  private:
    typename _Associative::const_iterator itr_; 
};

template <typename _Associative>
class const_value_iterator
{
  public:
    const_value_iterator() = delete;

    const_value_iterator(const typename _Associative::const_iterator& itr) : itr_(itr) {}

    void operator++() { itr_++; }
    const typename _Associative::mapped_type& operator*() const { return itr_->second; }

    bool operator==(const const_value_iterator& rhs) { return itr_ == rhs.itr_; }
    bool operator!=(const const_value_iterator& rhs) { return itr_ != rhs.itr_; }

  private:
    typename _Associative::const_iterator itr_; 
};

template <typename _Associative>
class reverse_value_iterator
{
  public:
    reverse_value_iterator() = delete;

    reverse_value_iterator(const typename _Associative::reverse_iterator& itr) : itr_(itr) {}

    void operator++() { itr_++; }
    typename _Associative::mapped_type& operator*() const { return itr_->second; }

    bool operator==(const reverse_value_iterator& rhs) { return itr_ == rhs.itr_; }
    bool operator!=(const reverse_value_iterator& rhs) { return itr_ != rhs.itr_; }

  private:
    typename _Associative::reverse_iterator itr_; 
};

template <typename _Associative>
class const_reverse_key_iterator
{
  public:
    const_reverse_key_iterator() = delete;

    const_reverse_key_iterator(const typename _Associative::const_reverse_iterator& itr) : itr_(itr) {}

    void operator++() { itr_++; }
    const typename _Associative::key_type& operator*() const { return itr_->first; }

    bool operator==(const const_reverse_key_iterator& rhs) { return itr_ == rhs.itr_; }
    bool operator!=(const const_reverse_key_iterator& rhs) { return itr_ != rhs.itr_; }

  private:
    typename _Associative::const_reverse_iterator itr_; 
};

template <typename _Associative>
class const_reverse_value_iterator
{
  public:
    const_reverse_value_iterator() = delete;

    const_reverse_value_iterator(const typename _Associative::const_reverse_iterator& itr) : itr_(itr) {}

    void operator++() { itr_++; }
    const typename _Associative::mapped_type& operator*() const { return itr_->second; }

    bool operator==(const const_reverse_value_iterator& rhs) { return itr_ == rhs.itr_; }
    bool operator!=(const const_reverse_value_iterator& rhs) { return itr_ != rhs.itr_; }

  private:
    typename _Associative::const_reverse_iterator itr_; 
};

}

#endif

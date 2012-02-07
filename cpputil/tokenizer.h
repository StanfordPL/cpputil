#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <cassert>
#include <iostream>
#include <map>

#include "bijection.h"
#include "serialize.h"

namespace cpputil
{

template <typename _T, 
          typename _Token = unsigned int,
          typename _Bijection = bijection<_T, _Token>>
class tokenizer
{
  // Friends
  friend class Serializer<tokenizer>;
  friend class Deserializer<tokenizer>;

  public:

    // Member types
    typedef          _T                                        value_type;
    typedef          const _T&                                 const_reference;
    typedef          _Token                                    token_type;
    typedef typename _Bijection::size_type                     size_type;
    typedef typename _Bijection::const_iterator                const_iterator;
    typedef typename _Bijection::const_reverse_iterator        const_reverse_iterator;
    typedef typename _Bijection::const_domain_iterator         const_value_iterator;
    typedef typename _Bijection::const_reverse_domain_iterator const_reverse_value_iterator;
    typedef typename _Bijection::const_range_iterator          const_token_iterator;
    typedef typename _Bijection::const_reverse_range_iterator  const_reverse_token_iterator;

    // Element access
    token_type tokenize(const_reference t)
    {
      if ( bijection_.domain_find(t) == bijection_.domain_end() )
      {
        token_type token = size();
        bijection_.insert(t, token);

        return token;
      }
      return bijection_.domain_assert_at(t);
    }
    const_reference untokenize(token_type token) const { return bijection_.range_assert_at(token); }

    // Iterators
    const_iterator begin() const { return bijection_.begin(); }
    const_iterator cbegin() const { return begin(); }
    const_iterator end() const { return bijection_.end(); }
    const_iterator cend() const { return end(); }

    const_value_iterator value_begin() const { return bijection_.domain_begin(); }
    const_value_iterator value_cbegin() const { return value_begin(); }
    const_value_iterator value_end() const { return bijection_.domain_end(); }
    const_value_iterator value_cend() const { return value_end(); }

    const_token_iterator token_begin() const { return bijection_.range_begin(); }
    const_token_iterator token_cbegin() const { return token_begin(); }
    const_token_iterator token_end() const { return bijection_.range_end(); }
    const_token_iterator token_cend() const { return token_end(); }

    // Capacity
    bool empty() const { return bijection_.empty(); }
    size_type size() const { return bijection_.size(); }

    // Modifiers
    void clear() { bijection_.clear(); }
    void swap(tokenizer& rhs) { bijection_.swap(rhs.bijection_); }

  private:
    _Bijection bijection_;
};

template <typename _T, typename _Token, typename _Bijection>
struct Serializer<tokenizer<_T, _Token, _Bijection>>
{
  static void serialize(std::ostream& os, const tokenizer<_T, _Token, _Bijection>& t, char delim = '"')
  {
    Serializer<_Bijection>::serialize(os, t.bijection_, delim);
  }
};

template <typename _T, typename _Token, typename _Bijection>
struct Deserializer<tokenizer<_T, _Token, _Bijection>>
{
  static void deserialize(std::istream& is, tokenizer<_T, _Token, _Bijection>& t, char delim = '"')
  {
    Deserializer<_Bijection>::deserialize(is, t.bijection_, delim);
  }
};

}

#endif

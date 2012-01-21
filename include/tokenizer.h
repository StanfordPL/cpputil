#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <cassert>
#include <deque>
#include <iostream>
#include <map>

#include "maputil.h"
#include "serialize.h"

namespace cpputil
{

template <typename _T, typename _Associative = std::map<const _T, unsigned int>, typename _Sequence = std::deque<const _T*> >
class tokenizer
{
  public:

    // Member types
    typedef          _T                               value_type;
    typedef          const _T&                        const_reference;
    typedef          unsigned int                     token_type;
    typedef typename _Sequence::size_type             size_type;
    typedef          const_key_iterator<_Associative> const_token_iterator;

    // Constructors
    tokenizer() {}
    tokenizer(const tokenizer& rhs)
    {
      valToToken_ = rhs.valToToken_;
      tokenToVal_.resize(valToToken_.size());
      for ( typename _Associative::value_type& i : valToToken_ )
        tokenToVal_[i.second] = &i.first;
    }
    tokenizer& operator=(tokenizer rhs)
    {
      swap(rhs);
      return *this;
    }

    // Element access
    token_type tokenize(const_reference t)
    {
      if ( valToToken_.find(t) == valToToken_.end() )
      {
        auto token = size();
        auto res = valToToken_.insert(typename _Associative::value_type(t, token));
        tokenToVal_.emplace_back(&(res.first->first));

        return token;
      }
      return valToToken_[t];
    }
    const_reference untokenize(token_type token) const
    {
      assert(token < size() && "Unrecognized token!");
      return *tokenToVal_[token];
    }

    // Iterators
    const_token_iterator begin() const { return const_key_iterator<_Associative>(valToToken_.begin()); }
    const_token_iterator cbegin() const { return const_key_iterator<_Associative>(valToToken_.begin()); }
    const_token_iterator end() const { return const_key_iterator<_Associative>(valToToken_.end()); }
    const_token_iterator cend() const { return const_key_iterator<_Associative>(valToToken_.end()); } 

    // Capacity
    bool empty() const { return tokenToVal_.empty(); }
    size_type size() const { return tokenToVal_.size(); }

    // Modifiers
    void clear()
    {
      valToToken_.clear();
      tokenToVal_.clear();
    }
    void swap(tokenizer& rhs)
    {
      valToToken_.swap(rhs.valToToken_);
      tokenToVal_.swap(rhs.tokenToVal_);
    }

  private:
    _Associative valToToken_;
    _Sequence tokenToVal_;
};

// TODO: This WONT preserve token->id mappings

template <typename _T>
struct Serializer<tokenizer<_T>>
{
  static void serialize(std::ostream& os, const tokenizer<_T>& t, char delim = '"')
  {
    os << t.size() << " ";
    for ( auto itr : t )
    {
      Serializer<_T>::serialize(os, itr, delim);
      os << " ";
    }
  }
};

template <typename _T>
struct Deserializer<tokenizer<_T>>
{
  static void deserialize(std::istream& is, tokenizer<_T>& t, char delim = '"')
  {
    t.clear();

    typename tokenizer<_T>::size_type size;
    is >> size;

    _T val;
    for ( auto i = 0; i < size; ++i )
    {
      Deserializer<_T>::deserialize(is, val, delim);
      t.tokenize(val);
    }
  }
};

}

#endif

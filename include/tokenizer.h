#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <cassert>
#include <deque>
#include <map>

#include "maputil.h"

namespace cpputil
{

template <typename _T, typename _Associative = std::map<const _T, unsigned int>, typename _Sequence = std::deque<const _T*> >
class tokenizer
{
  public:
    typedef          _T                               value_type;
    typedef          const _T&                        const_reference;
    typedef          unsigned int                     token_type;
    typedef typename _Sequence::size_type             size_type;
    typedef          const_key_iterator<_Associative> const_token_iterator;

    tokenizer()
    {
      // Does nothing.
    }
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

    const_token_iterator begin() const { return const_key_iterator<_Associative>(valToToken_.begin()); }
    const_token_iterator cbegin() const { return const_key_iterator<_Associative>(valToToken_.begin()); }
    const_token_iterator end() const { return const_key_iterator<_Associative>(valToToken_.end()); }
    const_token_iterator cend() const { return const_key_iterator<_Associative>(valToToken_.end()); } 

    bool empty() const { return tokenToVal_.empty(); }
    size_type size() const { return tokenToVal_.size(); }

    void swap(tokenizer& rhs)
    {
      valToToken_.swap(rhs.valToToken_);
      tokenToVal_.swap(rhs.tokenToVal_);
    }
    void clear()
    {
      valToToken_.clear();
      tokenToVal_.clear();
    }

    token_type tokenize(const_reference t)
    {
      if ( valToToken_.find(t) == valToToken_.end() )
      {
        auto token = size();
        auto entry = typename _Associative::value_type(t, token);
        auto res = valToToken_.insert(entry);
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

  private:
    _Associative valToToken_;
    _Sequence tokenToVal_;
};

}

#endif

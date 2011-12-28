#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <cassert>
#include <deque>
#include <map>

namespace cpputil
{

template <typename _T, typename _Associative = std::map<const _T, unsigned int>, typename _Sequence = std::deque<const _T*> >
class Tokenizer
{
  public:
    typedef          _T                   value_type;
    typedef          const _T&            const_reference;
    typedef          unsigned int         token_type;
    typedef typename _Sequence::size_type size_type;

    Tokenizer()
    {
      // Does nothing.
    }
    Tokenizer(const Tokenizer& rhs)
    {
      valToToken_ = rhs.valToToken_;
      tokenToVal_.resize(valToToken_.size());
      for ( typename _Associative::value_type& i : valToToken_ )
        tokenToVal_[i.second] = &i.first;
    }
    Tokenizer& operator=(Tokenizer rhs)
    {
      swap(rhs);
      return *this;
    }

    bool empty() const { return tokenToVal_.empty(); }
    size_type size() const { return tokenToVal_.size(); }

    void swap(Tokenizer& rhs)
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

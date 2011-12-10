#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <cassert>

#include <map>
#include <vector>

namespace cpputil
{

template <class T>
class Tokenizer
{
  public:
    typedef unsigned int Token;

    void clear();

    bool contains(const T& t) const;

    unsigned int size() const;

    Token tokenize(const T& t);
    const T& untokenize(Token token) const;

  private:
    std::map<const T, Token> valToToken_;
    std::vector<const T*> tokenToVal_;
};

template <class T>
void Tokenizer<T>::clear()
{
  valToToken_.clear();
  tokenToVal_.clear();
}

template <class T>
bool Tokenizer<T>::contains(const T& t) const
{
  return valToToken_.find(t) != valToToken_.end();
}

template <class T>
unsigned int Tokenizer<T>::size() const
{
  return valToToken_.size();
}

template <class T>
typename Tokenizer<T>::Token Tokenizer<T>::tokenize(const T& t)
{
  if ( ! contains(t) )
  {
    Token token = size();
    valToToken_[t] = token;

    auto itr = valToToken_.find(t);
    tokenToVal_.push_back(&itr->first);
  }

  return valToToken_[t];
}

template <class T>
const T& Tokenizer<T>::untokenize(Token token) const
{
  assert(token < tokenToVal_.size() && "Unrecognized token!");

  return *tokenToVal_[token];
}

}

#endif

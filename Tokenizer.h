#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "BiMap.h"

template <class T>
class Tokenizer
{
  public:
    typedef unsigned int Token;

    unsigned int size() const;

    void clear();

    Token tokenize(const T& t);
    T untokenize(Token token) const;

  private:
    BiMap<T, Token> contents_;
};

template <class T>
unsigned int Tokenizer<T>::size() const
{
  return contents_.size();
}

template <class T>
void Tokenizer<T>::clear()
{
  contents_.clear();
}

template <class T>
typename Tokenizer<T>::Token Tokenizer<T>::tokenize(const T& t)
{
  if ( !contents_.containsKey(t) )
    contents_.insert(t, contents_.size());

  return contents_.getVal(t);
}

template <class T>
T Tokenizer<T>::untokenize(Token token) const
{
  return contents_.getKey(token);
}

#endif

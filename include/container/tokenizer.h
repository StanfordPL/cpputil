/*
Copyright 2013 eric schkufza

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef CPPUTIL_INCLUDE_CONTAINER_TOKENIZER_H
#define CPPUTIL_INCLUDE_CONTAINER_TOKENIZER_H

#include <algorithm>
#include <stdint.h>
#include <unordered_map>

#include "include/container/bijection.h"

namespace cpputil {

template <typename T, typename Token = uint64_t, 
    typename TMap = std::unordered_map<T, Token>,
    typename TokenMap = std::unordered_map<Token, T>>
class Tokenizer {
  public:
    typedef T value_type;
    typedef const T& const_reference; 
    typedef Token token_type;
    typedef typename Bijection<T, Token, TMap, TokenMap>::size_type size_type;
    typedef typename Bijection<T, Token, TMap, TokenMap>::const_iterator const_iterator;

    Tokenizer() : next_token_{Token()} { }

    const_iterator tokenize(const_reference t) {
      const auto itr = contents_.domain_find(t);
      if ( itr == contents_.end() ) {
        return contents_.insert(std::make_pair(t, next_token_++)).first;
      } else {
        return itr;
      }
    }

    const_iterator untokenize(token_type token) const {
      return contents_.range_find(token); 
    }

    const_iterator begin() const {
      return contents_.begin();
    }

    const_iterator cbegin() const {
      return begin();
    }

    const_iterator end() const {
      return contents_.end();
    }

    const_iterator cend() const { 
      return end();
    }

    bool empty() const {
      return contents_.empty();
    }

    size_type size() const {
      return contents_.size();
    }

    void clear() {
      contents_.clear();
      next_token_ = Token();
    }

    void swap(Tokenizer& rhs) {
      contents_.swap(rhs.contents_);
      std::swap(next_token_, rhs.next_token);		
    }

  private:
    Bijection<T, Token, TMap, TokenMap> contents_;
    Token next_token_;
};

} // namespace cpputil

#endif

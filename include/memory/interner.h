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

#ifndef CPPUTIL_INCLUDE_MEMORY_INTERNER_H
#define CPPUTIL_INCLUDE_MEMORY_INTERNER_H

#include <unordered_set>
#include <utility>

namespace cpputil {

template <typename T, typename Set = std::unordered_set<T>>
class Interner {
  public:
    typedef T value_type;
    typedef const T& const_reference; 
    typedef typename Set::size_type size_type;
    typedef typename Set::const_iterator const_iterator;

    const_reference intern(const_reference t) {
      const auto res = vals_.insert(t);
      return *(res.first);
    }

    template <typename... T>
    const_reference intern(T&&... t) {
      const auto res = vals_.emplace(std::forward(t));
      return *(res.first);
    }

    bool empty() const {
      return vals_.empty();
    }

    size_type size() const {
      return vals_.size();
    }

    void clear() {
      vals_.clear();
    }

    void swap(Interner& rhs) {
      vals_.swap(rhs.vals_); 
    }

  private:
    Set vals_;
};

template <typename T, typename Set>
void swap(Interner<T,Set>& i1, Interner<T,Set>& i2) {
  i1.swap(i2);
}

} // namespace cpputil

#endif

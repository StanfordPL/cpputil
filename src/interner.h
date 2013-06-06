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

#ifndef CPPUTIL_SRC_INTERNER_H
#define CPPUTIL_SRC_INTERNER_H

#include <unordered_set>

namespace cpputil {

template <typename T, typename Set = std::unordered_set<T>>
class Interner {
  public:
    typedef T value_type;
    typedef const T& const_reference; 
    typedef typename Set::size_type size_type;
    typedef typename Set::const_iterator const_iterator;

    const_reference intern(const_reference t);

    const_iterator begin() const;
    const_iterator cbegin() const;
    const_iterator end() const; 
    const_iterator cend() const;

    bool empty() const;
    size_type size() const;

    void clear();
    void swap(Interner& rhs);

  private:
    Set vals_;
};

template <typename T, typename Set>
inline typename Interner<T, Set>::const_reference 
Interner<T, Set>::intern(const_reference t) {
	const auto res = vals_.insert(t);
	return *(res.first);
}

template <typename T, typename Set>
inline typename Interner<T, Set>::const_iterator
Interner<T, Set>::begin() const { 
	return vals_.begin(); 
}

template <typename T, typename Set>
inline typename Interner<T, Set>::const_iterator
Interner<T, Set>::cbegin() const { 
	return begin(); 
}

template <typename T, typename Set>
inline typename Interner<T, Set>::const_iterator
Interner<T, Set>::end() const { 
	return vals_.end(); 
}

template <typename T, typename Set>
inline typename Interner<T, Set>::const_iterator
Interner<T, Set>::cend() const { 
	return vals_.end(); 
}

template <typename T, typename Set>
inline bool Interner<T, Set>::empty() const { 
	return vals_.empty(); 
}

template <typename T, typename Set>
inline typename Interner<T, Set>::size_type Interner<T, Set>::size() const { 
	return vals_.size(); 
}

template <typename T, typename Set>
inline void Interner<T, Set>::clear() { 
	vals_.clear(); 
}

template <typename T, typename Set>
inline void Interner<T, Set>::swap(Interner& rhs) { 
	vals_.swap(rhs.vals_); 
}

} // namespace cpputil

#endif

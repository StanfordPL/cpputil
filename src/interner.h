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
    typedef typename Set::const_reverse_iterator const_reverse_iterator;

    const_reference intern(const_reference t);

    const_iterator begin() const;
    const_iterator cbegin() const;
    const_iterator end() const; 
    const_iterator cend() const;

    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;

    bool empty() const;
    size_type size() const;

    void clear();
    void swap(Interner& rhs);

  private:
    Set vals_;
};

template <typename T, typename Set>
inline Interner<T, Set>::const_reference 
Interner<T, Set>::intern(const_reference t) {
	auto res = vals_.insert(t);
	return *(res.first);
}

template <typename T, typename Set>
inline Interner<T, Set>::const_iterator
Interner<T, Set>::begin() const { 
	return vals_.begin(); 
}

template <typename T, typename Set>
inline Interner<T, Set>::const_iterator
Interner<T, Set>::cbegin() const { 
	return begin(); 
}

template <typename T, typename Set>
inline Interner<T, Set>::const_iterator
Interner<T, Set>::end() const { 
	return vals_.end(); 
}

template <typename T, typename Set>
inline Interner<T, Set>::const_iterator
Interner<T, Set>::cend() const { 
	return end(); 
}

template <typename T, typename Set>
inline Interner<T, Set>::const_reverse_iterator
Interner<T, Set>::rbegin() const { 
	return vals_.rbegin(); 
}

template <typename T, typename Set>
inline Interner<T, Set>::const_reverse_iterator
Interner<T, Set>::crbegin() const { 
	return rbegin(); 
}

template <typename T, typename Set>
inline Interner<T, Set>::const_reverse_iterator
Interner<T, Set>::rend() const { 
	return vals_.rend(); 
}

template <typename T, typename Set>
inline Interner<T, Set>::const_reverse_iterator
Interner<T, Set>::crend() const { 
	return rend(); 
}

template <typename T, typename Set>
inline bool Interner<T, Set>::empty() const { 
	return vals_.empty(); 
}

template <typename T, typename Set>
inline Interner<T, Set>::size_type Interner<T, Set>::size() const { 
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

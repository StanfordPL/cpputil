#ifndef ARRAY_H
#define ARRAY_H

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <stdexcept>

namespace cpputil
{

template <class T, int max>
class array
{
  public:

    // Member Types
    typedef T value_type;
    typedef ptrdiff_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<T*> reverse_iterator;
    typedef std::reverse_iterator<const T*> const_reverse_iterator;
    typedef T& reference;
    typedef const T& const_reference;

    // Constructors
    array() { }
    array(const T& t) { std::fill(begin(), end(), t); }
    array(const array& rhs) { std::copy(rhs.begin(), rhs.end(), begin()); }
    
    // Assignments
    array& operator=(const array& rhs)
    {
      std::copy(rhs.begin(), rhs.end(), begin());
      return *this;
    }

    // Conversion
    operator T*() { return xs; }

    // Iterators
    iterator begin() { return xs; }
    iterator end() { return xs + max; }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); } 

    const_iterator begin() const { return xs; }
    const_iterator end() const { return xs + max; }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
    
    // Element Access
    reference front() { return xs[0]; }
    reference back() { return xs[max-1]; }
    reference operator[](size_type i) { return xs[i]; }
    reference at(size_type i) 
    { 
      if ( i < 0 || i >= max ) 
        throw std::out_of_range("array::at"); 
      return xs[i]; 
    }

    const_reference front() const { return xs[0]; }
    const_reference back() const { return xs[max-1]; }
    const_reference operator[](size_type i) const { return xs[i]; }
    const_reference at(size_type i) const 
    { 
      if ( i < 0 || i >= max ) 
        throw std::out_of_range("array::at"); 
      return xs[i]; 
    }

    // Other Operations
    size_type size() const { return max; }
    size_type max_size() const { return max; }
    size_type capacity() const { return max; }
    void swap(array& rhs) { std::swap(xs, rhs.xs); }
    bool operator==(const array& rhs) const { return std::equal(begin(), end(), rhs.begin()); }
    bool operator!=(const array& rhs) const { return ! *this == rhs; }
    bool operator<(const array& rhs) const { return lexicographical_compare(begin(), end(), rhs.begin(), rhs.end()); }

  private:
    T xs[max];
};

}

#endif

#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <stdexcept>

namespace cpputil
{

template <class T, int max>
class array
{
  public:

    // Member Types
    typedef T         value_type;
    typedef ptrdiff_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T*        iterator;
    typedef const T*  const_iterator;
    typedef T*        reverse_iterator;
    typedef const T*  const_reverse_iterator;
    typedef T&        reference;
    typedef const T&  const_reference;

    // Constructors
    array() { }
    array(const T& t)
    {
      for ( auto i = 0; i < max; ++i )
        xs[i] = t;
    }
    array(const array& rhs)
    {
      for ( auto i = 0; i < max; ++i )
        xs[i] = rhs.x[i];
    }
    
    // Assignments
    array& operator=(const array& rhs)
    {
      if ( this != &rhs )
        for ( auto i = 0; i < max; ++i )
          xs[i] = rhs.xs[i];
      return *this;
    }

    // Conversion
    operator T*() { return xs; }

    // Iterators
    iterator begin() { return xs; }
    iterator end() { return xs + max; }
    reverse_iterator rbegin() { return xs + max - 1; }
    reverse_iterator rend() { return xs - 1; }

    const_iterator begin() const { return xs; }
    const_iterator end() const { return xs + max; }
    const_reverse_iterator rbegin() const { return xs + max - 1; }
    const_reverse_iterator rend() const { return xs - 1; }
    
    // Element Access
    reference front() { return xs[0]; }
    reference back() { return xs[max-1]; }
    reference operator[](size_type i) { return xs[i]; }
    reference at(size_type i) 
    { 
      if ( i < 0 || i >= max ) 
        throw out_of_range("array::at"); 
      return xs[i]; 
    }

    const_reference front() const { return xs[0]; }
    const_reference back() const { return xs[max-1]; }
    const_reference operator[](size_type i) const { return xs[i]; }
    const_reference at(size_type i) const 
    { 
      if ( i < 0 || i >= max ) 
        throw out_of_range("array::at"); 
      return xs[i]; 
    }

    // Other Operations
    size_type size() const { return max; }
    size_type max_size() const { return max; }
    size_type capacity() const { return max; }
    swap(array& rhs) 
    { 
      T* temp = xs;
      xs = rhs.xs;
      rhs.xs = temp;
    }
    bool operator==(const array& rhs) const 
    { 
      for ( auto i = 0; i < max; ++i )
        if ( xs[i] != rhs.xs[i] )
          return false;
      return true;
    }
    bool operator!=(const array& rhs) const 
    { 
      for ( auto i = 0; i < max; ++i )
        if ( xs[i] != rhs.xs[i] )
          return true;
      return false;
    }
    bool operator<(const array& rhs) const 
    { 
      for ( auto i = 0; i < max; ++i )
        if ( xs[i] < rhs.xs[i] )
          return true;
        else if ( xs[i] > rhs.xs[i] )
          return false;
      return false;
    }

  private:
    T xs[max];
};

}

#endif

#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

namespace cpputil
{

template <class T, int max>
class array
{
  public:
    typedef T value_type;

    typedef T* iterator;
    typedef const T* const_iterator;

    typedef T& reference;
    typedef const T& const_reference;

    operator T*() { return v; }

    reference operator[](ptrdiff_t i) { return v[i]; }
    const_reference operator[](ptrdiff_t i) const { return v[i]; }

    iterator begin() { return v; }
    const_iterator begin() const { return v; }

    iterator end() { return v + max; }
    const_iterator end() const { return v + max; }

    size_t size() const { return max; }

  private:
    T v[max];
};

}

#endif

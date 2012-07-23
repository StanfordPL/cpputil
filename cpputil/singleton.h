#ifndef CPPUTIL_SINGLETON_H
#define CPPUTIL_SINGLETON_H

namespace cpputil
{

template <typename T>
struct singleton
{
  // Member types
  typedef T& reference;

  // Constructors
  singleton() = delete;
  singleton(const singleton& s) = delete;
  singleton& operator=(singleton s) = delete;

  // Element access
  static inline reference get()
  {
    static _T instance;
    return instance;
  }
};

}

#endif

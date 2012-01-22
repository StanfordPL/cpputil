#ifndef SINGLETON_H
#define SINGLETON_H

namespace cpputil
{

template <typename _T>
struct singleton
{
  // Member types
  typedef _T& reference;

  // Constructors
  singleton() = delete;
  singleton(const singleton& s) = delete;
  singleton& operator=(singleton s) = delete;

  // Element access
  static reference get()
  {
    static _T instance;
    return instance;
  }
};

}

#endif

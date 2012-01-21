#ifndef SINGLETON_H
#define SINGLETON_H

namespace cpputil
{

template <typename _T>
struct Singleton
{
  // Member types
  typedef _T& reference;

  // Constructors
  Singleton() = delete;
  Singleton(const Singleton& s) = delete;
  Singleton& operator=(Singleton s) = delete;

  // Element access
  static reference get()
  {
    static _T instance;
    return instance;
  }
};

}

#endif

#ifndef SINGLETON_H
#define SINGLETON_H

namespace cpputil
{

template <typename _T>
struct Singleton
{
  typedef _T  value_type;
  typedef _T& reference;

  Singleton() = delete;
  Singleton(const Singleton& s) = delete;
  Singleton& operator=(const Singleton& s) = delete;

  static reference get()
  {
    static value_type instance;
    return instance;
  }
};

}

#endif

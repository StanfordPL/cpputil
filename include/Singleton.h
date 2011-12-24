#ifndef SINGLETON_H
#define SINGLETON_H

namespace cpputil
{

template <class T>
struct Singleton
{
  Singleton() = delete;
  Singleton(const Singleton& s) = delete;
  Singleton& operator=(const Singleton& s) = delete;

  static T& get()
  {
    static T instance;
    return instance;
  }
};

}

#endif

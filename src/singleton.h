#ifndef CPPUTIL_SRC_SINGLETON_H
#define CPPUTIL_SRC_SINGLETON_H

namespace cpputil {

template <typename T>
struct Singleton {
  typedef T& reference;

  Singleton() = delete;
  Singleton(const Singleton& s) = delete;
  Singleton& operator=(Singleton s) = delete;

  static reference get();
};

template <typename T>
inline typename Singleton<T>::reference Singleton<T>::get() {
  static T instance;
  return instance;
}

} // namespace cpputil

#endif

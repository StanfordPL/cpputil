/*
Copyright 2013 eric schkufza

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef CPPUTIL_SRC_SINGLETON_H
#define CPPUTIL_SRC_SINGLETON_H

namespace cpputil {

template <typename T>
class Singleton {
	public:
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

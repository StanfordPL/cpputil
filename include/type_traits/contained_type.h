#ifndef CPPUTIL_INCLUDE_TYPE_TRAITS_CONTAINED_TYPE_H
#define CPPUTIL_INCLUDE_TYPE_TRAITS_CONTAINED_TYPE_H

#include <type_traits>

#include "include/type_traits/is_stl_sequence.h"

namespace cpputil {

template <typename T, typename Ignore = void>
struct contained_type {
	typedef T type;
};

template <typename T>
struct contained_type<T, typename std::enable_if<is_stl_sequence<T>::value>::type> {
	typedef typename contained_type<typename T::value_type>::type type;
};

} // namespace cpputil

#endif

// Copyright 2014 eric schkufza
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CPPUTIL_INCLUDE_SERIALIZE_STL_DEBUG_H
#define CPPUTIL_INCLUDE_SERIALIZE_STL_DEBUG_H

#include <iostream>
#include <type_traits>

#include "include/meta/is_stl_container.h"
#include "include/serialize/text_reader.h"
#include "include/serialize/text_writer.h"

template <typename T>
typename std::enable_if<cpputil::is_stl_container<T>::value, std::ostream&>::type 
		operator<<(std::ostream& os, const T& t) {
	cpputil::TextWriter<T> tw;
	tw(os, t);
	return os;
}

template <typename T>
typename std::enable_if<cpputil::is_stl_container<T>::value, std::istream&>::type 
		operator>>(std::istream& is, T& t) {
	cpputil::TextReader<T> tr;
	tr(is, t);
	return is;
}

#endif

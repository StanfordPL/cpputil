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

#ifndef CPPUTIL_INCLUDE_SERIALIZE_TEXT_WRITER_H
#define CPPUTIL_INCLUDE_SERIALIZE_TEXT_WRITER_H

#include <iostream>
#include <type_traits>

#include "include/type_traits/is_stl_associative.h"
#include "include/type_traits/is_stl_map.h"
#include "include/type_traits/is_stl_sequence.h"
#include "include/type_traits/is_stl_set.h"

namespace cpputil {

template <typename T, char Open = '{', char Close = '}', char Quote = '"', typename Enable = void>
struct TextWriter;

template <typename T, char Open, char Close, char Quote>
struct TextWriter < T, Open, Close, Quote,
    typename std::enable_if < std::is_scalar<T>::value&&  !std::is_enum<T>::value >::type > {
  void operator()(std::ostream& os, const T& t) const {
    os << t;
  }
};

template <typename T, char Open, char Close, char Quote>
struct TextWriter < T, Open, Close, Quote,
    typename std::enable_if < std::is_scalar<T>::value&&  std::is_enum<T>::value >::type > {
  void operator()(std::ostream& os, const T& t) const {
    os << (typename std::underlying_type<T>::type) t;
  }
};

template <char Open, char Close, char Quote>
struct TextWriter<std::string, Open, Close, Quote, void> {
  void operator()(std::ostream& os, const std::string& s) const {
    os << Quote << s << Quote;
  }
};

template <typename T1, typename T2, char Open, char Close, char Quote>
struct TextWriter<std::pair<T1, T2>, Open, Close, Quote, void> {
  void operator()(std::ostream& os, const std::pair<T1, T2>& p) const {
    os << Open << " ";

    TextWriter<T1, Open, Close, Quote> w1;
    w1(os, p.first);

    os << " ";

    TextWriter<T2, Open, Close, Quote> w2;
    w2(os, p.second);

    os << " " << Close;
  }
};

template <typename T, char Open, char Close, char Quote>
struct TextWriter < T, Open, Close, Quote,
    typename std::enable_if < is_stl_sequence<T>::value || is_stl_associative<T>::value >::type > {
  void operator()(std::ostream& os, const T& t) const {
    TextWriter<typename T::value_type, Open, Close, Quote> w;

    os << Open;
    for (auto i = t.begin(), ie = t.end(); i != ie; ++i) {
      os << " ";
      w(os, *i);
    }
    os << " " << Close;
  }
};

} // namespace cpputil

#endif


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

#ifndef CPPUTIL_INCLUDE_SERIALIZE_TEXT_READER_H
#define CPPUTIL_INCLUDE_SERIALIZE_TEXT_READER_H

#include <iostream>
#include <type_traits>

#include "include/type_traits/is_stl_associative.h"
#include "include/type_traits/is_stl_map.h"
#include "include/type_traits/is_stl_sequence.h"
#include "include/type_traits/is_stl_set.h"

namespace cpputil {

template <typename T, char Open = '{', char Close = '}', char Quote = '"', typename Enable = void>
struct TextReader;

template <typename T, char Open, char Close, char Quote>
struct TextReader < T, Open, Close, Quote,
    typename std::enable_if < std::is_scalar<T>::value&&  !std::is_enum<T>::value >::type > {
  void operator()(std::istream& is, T& t) const {
    is >> t;
  }
};

template <typename T, char Open, char Close, char Quote>
struct TextReader < T, Open, Close, Quote,
    typename std::enable_if < std::is_scalar<T>::value&&  std::is_enum<T>::value >::type > {
  void operator()(std::istream& is, T& t) const {
    typename std::underlying_type<T>::type v;
    is >> v;
    t = (T)v;;
  }
};

template <char Open, char Close, char Quote>
struct TextReader<std::string, Open, Close, Quote, void> {
  void operator()(std::istream& is, std::string& s) const {
    if (is.get() != Quote) {
      is.setstate(std::ios::failbit);
    }
    std::getline(is, s, Quote);
  }
};

template <typename T1, typename T2, char Open, char Close, char Quote>
struct TextReader<std::pair<T1, T2>, Open, Close, Quote, void> {
  void operator()(std::istream& is, std::pair<T1, T2>& p) const {
    auto die_unless = [](std::istream & is, char c) {
      if (is.get() != c) {
        is.setstate(std::ios::failbit);
      }
    };

    die_unless(is, Open);
    die_unless(is, ' ');

    TextReader<T1, Open, Close, Quote> r1;
    r1(is, p.first);

    die_unless(is, ' ');

    TextReader<T2, Open, Close, Quote> r2;
    r2(is, p.second);

    die_unless(is, ' ');
    die_unless(is, Close);
  }
};

template <typename T, char Open, char Close, char Quote>
struct TextReader<T, Open, Close, Quote,
    typename std::enable_if<is_stl_sequence<T>::value>::type> {
  void operator()(std::istream& is, T& t) const {
    auto die_unless = [](std::istream & is, char c) {
      if (is.get() != c) {
        is.setstate(std::ios::failbit);
      }
    };

    die_unless(is, Open);
    die_unless(is, ' ');

    t.clear();
    while (is.peek() != Close) {
      typename T::value_type v;
      TextReader<decltype(v), Open, Close, Quote> r;
      r(is, v);
      t.push_back(v);

      die_unless(is, ' ');
    }
    die_unless(is, Close);
  }
};

template <typename T, char Open, char Close, char Quote>
struct TextReader<T, Open, Close, Quote,
    typename std::enable_if<is_stl_set<T>::value>::type> {
  void operator()(std::istream& is, T& t) const {
    auto die_unless = [](std::istream & is, char c) {
      if (is.get() != c) {
        is.setstate(std::ios::failbit);
      }
    };

    die_unless(is, Open);
    die_unless(is, ' ');

    t.clear();
    while (is.peek() != Close) {
      typename T::value_type v;
      TextReader<decltype(v), Open, Close, Quote> r;
      r(is, v);
      t.insert(v);

      die_unless(is, ' ');
    }
    die_unless(is, Close);
  }
};

template <typename T, char Open, char Close, char Quote>
struct TextReader<T, Open, Close, Quote,
    typename std::enable_if<is_stl_map<T>::value>::type> {
  void operator()(std::istream& is, T& t) const {
    auto die_unless = [](std::istream & is, char c) {
      if (is.get() != c) {
        is.setstate(std::ios::failbit);
      }
    };

    die_unless(is, Open);
    die_unless(is, ' ');

    t.clear();
    while (is.peek() != Close) {
      std::pair<typename std::remove_const<typename T::key_type>::type, typename T::mapped_type> v;
      TextReader<decltype(v), Open, Close, Quote> r;
      r(is, v);
      t.insert(v);

      die_unless(is, ' ');
    }
    die_unless(is, Close);
  }
};

} // namespace cpputil

#endif



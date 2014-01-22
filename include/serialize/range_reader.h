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

#ifndef CPPUTIL_INCLUDE_SERIALIZE_RANGE_READER_H
#define CPPUTIL_INCLUDE_SERIALIZE_RANGE_READER_H

#include <iostream>
#include <type_traits>

#include "include/serialize/text_reader.h"
#include "include/type_traits/is_stl_sequence.h"
#include "include/type_traits/is_stl_set.h"

namespace cpputil {

template <typename T, typename T::value_type Min, typename T::value_type Max,
          typename R = TextReader<typename T::value_type>, char Open = '{', char Close = '}',
          char Etc = '.', typename Enable = void>
struct RangeReader;

template <typename T, typename T::value_type Min, typename T::value_type Max, typename R, char Open,
          char Close, char Etc>
struct RangeReader<T, Min, Max, R, Open, Close, Etc,
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
    auto range = false;

    while (is.peek() != Close) {
      if (is.peek() == Etc) {
        range = true;
        while (is.peek() == Etc) {
          is.get();
        }
      } else {
        typename T::value_type v;
        R r;
        r(is, v);

        if (range) {
          range = false;
          if (t.empty()) {
            t.push_back(Min);
          }
          auto vv = t.back();
          for (++vv; vv < v; ++vv) {
            t.push_back(vv);
          }
        }
        t.push_back(v);
      }

      die_unless(is, ' ');
    }
    die_unless(is, Close);

    if (range) {
      if (t.empty()) {
        t.push_back(Min);
      }
      auto v = t.back();
      for (++v; v < Max; ++v) {
        t.push_back(v);
      }
    }
  }
};

template <typename T, typename T::value_type Min, typename T::value_type Max, typename R, char Open,
          char Close, char Etc>
struct RangeReader<T, Min, Max, R, Open, Close, Etc,
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
    auto range = false;
    auto last_insert = Min;

    while (is.peek() != Close) {
      if (is.peek() == Etc) {
        range = true;
        while (is.peek() == Etc) {
          is.get();
        }
      } else {
        typename T::value_type v;
        R r;
        r(is, v);

        if (range) {
          range = false;
          if (t.empty()) {
            t.insert(Min);
          }
          auto vv = last_insert;
          for (++vv; vv < v; ++vv) {
            t.insert(vv);
          }
        }
        t.insert(v);
        last_insert = v;
      }

      die_unless(is, ' ');
    }
    die_unless(is, Close);

    if (range) {
      if (t.empty()) {
        t.insert(Min);
      }
      auto v = last_insert;
      for (++v; v < Max; ++v) {
        t.insert(v);
      }
    }
  }
};

} // namespace cpputil

#endif

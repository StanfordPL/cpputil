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

#ifndef CPPUTIL_INCLUDE_SERIALIZE_SPAN_READER_H
#define CPPUTIL_INCLUDE_SERIALIZE_SPAN_READER_H

#include <iostream>
#include <type_traits>

#include "include/meta/is_stl_sequence.h"
#include "include/meta/is_stl_set.h"
#include "include/serialize/range.h"
#include "include/serialize/text_reader.h"
#include "include/serialize/text_style.h"

namespace cpputil {

#define die_unless(c) \
	if (is.get() != c) { \
		is.setstate(std::ios::failbit); \
		return; \
	}

#define die_outside(v, l,u) \
	if (v < l || v > u) { \
		is.setstate(std::ios::failbit); \
		return; \
	}

template <typename T, typename Range, typename Style = TextStyle<>, typename Enable = void>
struct SpanReader;

template <typename T, typename Range, typename Style>
class SpanReader<T, Range, Style, typename std::enable_if<is_stl_sequence<T>::value>::type> {
 public:
  void operator()(std::istream& is, T& t) const {
    die_unless(Style::open());
    die_unless(' ');

    t.clear();
    auto range = false;

    while (is.peek() != Style::close()) {
      if (is.peek() == Style::etc()) {
        range = true;
        while (is.peek() == Style::etc()) {
          is.get();
        }
      } else {
        typename T::value_type v;
        TextReader<typename T::value_type, Style>()(is, v);
        die_outside(v, Range::lower(), Range::upper());

        if (range) {
          range = false;
          fill_until(t, v);
        }
        t.emplace_back(v);
      }

      die_unless(' ');
    }
    die_unless(Style::close());

    if (range) {
      fill_until(t, Range::upper());
			t.emplace_back(Range::upper());
    }
  }

 private:
  void fill_until(T& t, const typename T::value_type& v) const {
    if (t.empty()) {
      t.emplace_back(Range::lower());
    }
    auto last = t.back();
    for (++last; last < v; ++last) {
      t.emplace_back(last);
    }
  }
};

template <typename T, typename Range, typename Style>
struct SpanReader<T, Range, Style, typename std::enable_if<is_stl_set<T>::value>::type> {
 public:
  void operator()(std::istream& is, T& t) const {
    die_unless(Style::open());
    die_unless(' ');

    t.clear();
    auto range = false;
    auto last = Range::lower();

    while (is.peek() != Style::close()) {
      if (is.peek() == Style::etc()) {
        range = true;
        while (is.peek() == Style::etc()) {
          is.get();
        }
      } else {
        typename T::value_type v;
        TextReader<typename T::value_type, Style>()(is, v);
        die_outside(v, Range::lower(), Range::upper());

        if (range) {
          range = false;
          fill_until(t, last, v);
        }
        t.emplace(v);
        last = v;
      }

      die_unless(' ');
    }
    die_unless(Style::close());

    if (range) {
      fill_until(t, last, Range::upper());
			t.emplace(Range::upper());
    }
  }

 private:
  void fill_until(T& t, typename T::value_type last, const typename T::value_type& v) const {
    if (t.empty()) {
      t.emplace(Range::lower());
    }
    for (++last; last < v; ++last) {
      t.emplace(last);
    }
  }
};

#undef die_unless
#undef die_outside

} // namespace cpputil

#endif


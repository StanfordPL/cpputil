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

#include "include/meta/is_stl_map.h"
#include "include/meta/is_stl_pair.h"
#include "include/meta/is_stl_sequence.h"
#include "include/meta/is_stl_set.h"
#include "include/meta/is_stl_string.h"
#include "include/meta/is_stl_tuple.h"
#include "include/serialize/dec_reader.h"
#include "include/serialize/hex_reader.h"
#include "include/serialize/text_style.h"

namespace cpputil {

#define die_unless(c) \
	if (is.get() != c) { \
		is.setstate(std::ios::failbit); \
		return; \
	}

template <typename T, typename Style = TextStyle<>, typename Enable = void>
struct TextReader;

template <typename T, typename Style>
struct TextReader <T, Style, typename std::enable_if <std::is_arithmetic<T>::value>::type> {
  void operator()(std::istream& is, T& t) const {
		if ( Style::dec() ) {
			DecReader<T>()(is, t);
		} else {
			HexReader<T, Style::hex_group()>()(is, t);
		}
  }
};

template <typename T, typename Style>
struct TextReader<T, Style, typename std::enable_if<is_stl_string<T>::value>::type> {
  void operator()(std::istream& is, T& t) const {
    if (is.peek() == Style::quote()) {
      is.get();
      std::getline(is, t, Style::quote());
    } else {
      is >> t;
    }
  }
};

template <typename T, typename Style>
struct TextReader<T, Style, typename std::enable_if <is_stl_pair<T>::value>::type> {
  void operator()(std::istream& is, T& t) const {
    die_unless(Style::open());
    die_unless(' ');

    TextReader<typename T::first_type, Style>()(is, t.first);
    die_unless(' ');
    TextReader<typename T::second_type, Style>()(is, t.second);

    die_unless(' ');
    die_unless(Style::close());
  }
};

template <typename T, typename Style>
struct TextReader<T, Style, typename std::enable_if<is_stl_sequence<T>::value>::type> {
  void operator()(std::istream& is, T& t) const {
    die_unless(Style::open());
    die_unless(' ');

    t.clear();
    while (is.peek() != Style::close()) {
      typename T::value_type v;
      TextReader<decltype(v), Style>()(is, v);
      t.emplace_back(v);

      die_unless(' ');
    }
    die_unless(Style::close());
  }
};

template <typename T, typename Style>
struct TextReader<T, Style, typename std::enable_if<is_stl_set<T>::value>::type> {
  void operator()(std::istream& is, T& t) const {
    die_unless(Style::open());
    die_unless(' ');

    t.clear();
    while (is.peek() != Style::close()) {
      typename T::value_type v;
      TextReader<decltype(v), Style>()(is, v);
      t.emplace(v);

      die_unless(' ');
    }
    die_unless(Style::close());
  }
};

template <typename T, typename Style>
struct TextReader<T, Style, typename std::enable_if<is_stl_map<T>::value>::type> {
  void operator()(std::istream& is, T& t) const {
    die_unless(Style::open());
    die_unless(' ');

    t.clear();
    while (is.peek() != Style::close()) {
      std::pair<typename std::remove_const<typename T::key_type>::type, typename T::mapped_type> v;
      TextReader<decltype(v), Style>()(is, v);
      t.emplace(v);

      die_unless(' ');
    }
    die_unless(Style::close());
  }
};

template <typename T, typename Style>
class TextReader <T, Style, typename std::enable_if <is_stl_tuple<T>::value>::type> {
 public:
  void operator()(std::istream& is, const T& t) const {
    die_unless(Style::open());
    Helper<T, 0, std::tuple_size<T>::value>()(is, t);
    die_unless(' ');
    die_unless(Style::close());
  }

 private:
  template <typename Tuple, size_t Begin, size_t End>
  struct Helper {
    void operator()(std::istream& is, const Tuple& t) {
      die_unless(' ');
      TextReader<typename std::tuple_element<Begin, Tuple>::type, Style>()(is, std::get<Begin>(t));
      Helper < Tuple, Begin + 1, End > ()(is, t);
    }
  };

  template <typename Tuple, size_t End>
  struct Helper<Tuple, End, End> {
    void operator()(std::istream& is, const Tuple& t) { }
  };
};

#undef die_unless

} // namespace cpputil

#endif

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

#include "include/meta/is_char_pointer.h"
#include "include/meta/is_stl_associative.h"
#include "include/meta/is_stl_sequence.h"
#include "include/meta/is_stl_pair.h"
#include "include/meta/is_stl_string.h"
#include "include/meta/is_stl_tuple.h"
#include "include/serialize/dec_writer.h"
#include "include/serialize/hex_writer.h"
#include "include/serialize/text_style.h"

namespace cpputil {

template <typename T, typename Style = TextStyle<>, typename Enable = void>
struct TextWriter;

template <typename T, typename Style>
struct TextWriter <T, Style, typename std::enable_if <std::is_arithmetic<T>::value>::type> {
  void operator()(std::ostream& os, const T& t) const {
		if ( Style::dec() ) {
			DecWriter<T>()(os, t);
		} else {
			HexWriter<T, Style::hex_group()>()(os, t);
		}
  }
};

template <typename T, typename Style>
struct TextWriter < T, Style,
    typename std::enable_if < is_char_pointer<T>::value || is_stl_string<T>::value >::type > {
  void operator()(std::ostream& os, const T& t) const {
    os << Style::quote() << t << Style::quote();
  }
};

template <typename T, typename Style>
struct TextWriter<T, Style, typename std::enable_if <is_stl_pair<T>::value>::type> {
  void operator()(std::ostream& os, const T& t) const {
    os << Style::open() << " ";

    TextWriter<typename T::first_type, Style>()(os, t.first);
    os << " ";
    TextWriter<typename T::second_type, Style>()(os, t.second);

    os << " " << Style::close();
  }
};

template <typename T, typename Style>
struct TextWriter < T, Style,
    typename std::enable_if < is_stl_sequence<T>::value || is_stl_associative<T>::value >::type > {
  void operator()(std::ostream& os, const T& t) const {
    os << Style::open();

    for (auto& elem : t) {
      os << " ";
      TextWriter<typename T::value_type, Style>()(os, elem);
    }

    os << " " << Style::close();
  }
};

template <typename T, typename Style>
class TextWriter <T, Style, typename std::enable_if <is_stl_tuple<T>::value>::type> {
 public:
  void operator()(std::ostream& os, const T& t) const {
    os << Style::open();
    Helper<T, 0, std::tuple_size<T>::value>()(os, t);
    os << " " << Style::close();
  }

 private:
  template <typename Tuple, size_t Begin, size_t End>
  struct Helper {
    void operator()(std::ostream& os, const Tuple& t) {
      os << " ";
      TextWriter<typename std::tuple_element<Begin, Tuple>::type, Style>()(os, std::get<Begin>(t));
      Helper < Tuple, Begin + 1, End > ()(os, t);
    }
  };

  template <typename Tuple, size_t End>
  struct Helper<Tuple, End, End> {
    void operator()(std::ostream& os, const Tuple& t) { }
  };
};

} // namespace cpputil

#endif


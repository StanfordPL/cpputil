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

#ifndef CPPUTIL_INCLUDE_SERIALIZE_SPAN_WRITER_H
#define CPPUTIL_INCLUDE_SERIALIZE_SPAN_WRITER_H

#include <iostream>
#include <type_traits>
#include <algorithm>

namespace cpputil {

template <typename T, typename Range, typename Style = TextStyle<>, typename Enable = void>
struct SpanWriter;

template <typename T, typename Range, typename Style>
struct SpanWriter<T, Range, Style, typename std::enable_if<is_stl_sequence<T>::value>::type> {
 public:
  void operator()(std::ostream& os, const T& t) const {
    std::vector<typename T::value_type> v(t.size());
    std::copy(t.begin(), t.end(), v.begin());
    std::sort(v.begin(), v.end());

    os << Style::open();

    typename T::value_type last = v[0];
    typename T::value_type last_run_start = v[0];
    bool use_open_range = false; // using open ranges seems to make the result less readable
    int run = -1;
    for (auto cur : v) {
      if (cur == last + 1) {
        // we are in a run
        ++run;
      } else {
        if (run > 2) {
          // end current run
          if (last_run_start != Range::lower() || !use_open_range) {
            os << " " << last_run_start;
          }
          os << " ... " << last;
        } else if (run == 2) {
          os << " " << last_run_start << " " << last;
        } else if (run >= 0) {
          os << " " << last;
        }
        run = 1;
        last_run_start = cur;
      }
      last = cur;
    }

    if (run > 0) {
      if (run > 2) {
        // end current run
        if (last_run_start != Range::lower() || !use_open_range) {
          os << " " << last_run_start;
        }
        os << " ...";
        if (last != Range::upper() || !use_open_range) {
          os << " " << last;
        }
      } else if (run == 2) {
        os << " " << last_run_start << " " << last;
      } else {
        os << " " << last;
      }
    }

    os << " " << Style::close();
  }
};

template <typename T, typename Range, typename Style>
struct SpanWriter<T, Range, Style, typename std::enable_if<is_stl_set<T>::value>::type> {
 public:
  void operator()(std::ostream& os, const T& t) const {
    std::vector<typename T::value_type> v(t.size());
    std::copy(t.begin(), t.end(), v.begin());
    SpanWriter<std::vector<typename T::value_type>, Range, Style> w;
    w(os, v);
  }
};

} // namespace cpputil

#endif
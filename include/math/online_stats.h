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

#ifndef CPPUTIL_INCLUDE_MATH_ONLINE_STATS_H
#define CPPUTIL_INCLUDE_MATH_ONLINE_STATS_H

#include <type_traits>

namespace cpputil {

/** Credit goes to: http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#On-line_algorithm */
template <typename T, typename Enable = void>
class OnlineStats;

template <typename T>
class OnlineStats <T, typename std::enable_if<std::is_arithmetic<T>::value>::type> {
 public:
  OnlineStats() : n_(0), mean_(0) { }

  void push_back(T t) {
    n_++;
    const auto delta = t - mean_;
    mean_ += delta / n_;
    m2_ += delta * (t - mean_);
  }

  size_t size() const {
    return n_;
  }

  T mean() const {
    return mean_;
  }

  T variance() const {
    return n_ < 2 ? 0 : m2_ / (n_ - 1);
  }

 private:
  size_t n_;
  T mean_;
  T m2_;
};

} // namespace cpputil

#endif

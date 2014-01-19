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

#ifndef CPPUTIL_INCLUDE_CONTAINER_BIJECTION_H
#define CPPUTIL_INCLUDE_CONTAINER_BIJECTION_H

#include <initializer_list>
#include <map>

namespace cpputil {

template <typename D, typename R, typename DMap = std::map<D, R>,
          typename RMap = std::map<R, D>>
class Bijection {
 public:
  typedef D domain_type;
  typedef const domain_type& const_domain_reference;
  typedef R range_type;
  typedef const range_type& const_range_reference;
  typedef typename DMap::const_iterator const_iterator;
  typedef typename DMap::value_type value_type;
  typedef const value_type& const_reference;
  typedef typename DMap::size_type size_type;

  const_iterator begin() const {
    return d2r_.begin();
  }

  const_iterator cbegin() const {
    return d2r_.cbegin();
  }

  const_iterator end() const {
    return d2r_.end();
  }

  const_iterator cend() const {
    return d2r_.cend();
  }

  bool empty() const {
    return d2r_.empty();
  }

  size_type size() const {
    return d2r_.size();
  }

  void clear() {
    d2r_.clear();
    r2d_.clear();
  }

  std::pair<const_iterator, bool> insert(const value_type& val) {
    if (d2r_.find(val.first) != d2r_.end() || r2d_.find(val.second) != r2d_.end()) {
      return std::make_pair(end(), false);
    } else {
      r2d_.insert(std::make_pair(val.second, val.first));
      return d2r_.insert(val);
    }
  }

  template <typename InputIterator>
  void insert(InputIterator first, InputIterator last) {
    for (; first != last; ++first) {
      insert(*first);
    }
  }

  void insert(std::initializer_list<value_type> il) {
    for (const auto& i : il) {
      insert(*i);
    }
  }

  const_iterator erase(const_iterator position) {
    r2d_.erase(position->second);
    return d2r_.erase(position);
  }

  size_type domain_erase(const_domain_reference val) {
    const auto itr = d2r_.find(val);
    if (itr != d2r_.end()) {
      r2d_.erase(itr->second);
      return d2r_.erase(val);
    } else {
      return 0;
    }
  }

  size_type range_erase(const_range_reference val) {
    const auto itr = r2d_.find(val);
    if (itr != r2d_.end()) {
      const auto ret = d2r_.erase(itr->second);
      r2d_.erase(itr->second);
      return ret;
    } else {
      return 0;
    }
  }

  const_iterator erase(const_iterator first, const_iterator last) {
    for (auto temp = first; temp != last; ++temp) {
      r2d_.erase(temp->second);
    }
    return d2r_.erase(first, last);
  }

  const_iterator domain_find(const_domain_reference d) const {
    return d2r_.find(d);
  }

  const_iterator range_find(const_range_reference r) const {
    const auto itr = r2d_.find(r);
    return itr != r2d_.end() ? domain_find(itr->second) : end();
  }

  const_reference domain_at(const_domain_reference d) const {
    return d2r_.at(d);
  }

  const_reference range_at(const_range_reference r) const {
    const auto& val = r2d_.at(r);
    return d2r_.at(val.second);
  }

  void swap(Bijection& rhs) {
    d2r_.swap(rhs.d2r_);
    r2d_.swap(rhs.r2d_);
  }

 private:
  DMap d2r_;
  RMap r2d_;
};

} // namespace cpputil

#endif

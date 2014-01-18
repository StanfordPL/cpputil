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

#ifndef CPPUTIL_INCLUDE_CONTAINER_MAP_UTIL_H
#define CPPUTIL_INCLUDE_CONTAINER_MAP_UTIL_H

#include <cassert>

namespace cpputil {

template <typename Map>
class CppUtilMap : public Map {
  public:
    typedef Map map_type;

    class const_key_iterator {
      public:
        const_key_iterator() = delete;
        const_key_iterator(const typename map_type::const_iterator& itr) 
          : itr_{itr} { }

        const_key_iterator& operator++() {
          itr_++;
          return *this;
        }

        const typename map_type::key_type& operator*() const {
          return itr_->first;
        }

        bool operator==(const const_key_iterator& rhs) const {
          return itr_ == rhs.itr_;
        }

        bool operator!=(const const_key_iterator& rhs) const {
          return itr_ != rhs.itr_;
        }

      private:
        typename map_type::const_iterator itr_; 
    };

    class value_iterator {
      public:
        value_iterator() = delete;
        value_iterator(const typename map_type::iterator& itr)
          : itr_{itr} { }

        value_iterator& operator++() {
          itr_++;
          return *this;
        }

        typename map_type::mapped_type& operator*() const {
          return itr_->second;
        }

        bool operator==(const value_iterator& rhs) const {
          return itr_ == rhs.itr_;
        }

        bool operator!=(const value_iterator& rhs) const {
          return itr_ != rhs.itr_;
        }

      private:
        typename map_type::iterator itr_; 
    };

    class const_value_iterator {
      public:
        const_value_iterator() = delete;
        const_value_iterator(const typename map_type::const_iterator& itr)
          : itr_{itr} { }

        const_value_iterator& operator++() {
          itr_++;
          return *this;
        }

        const typename map_type::mapped_type& operator*() const {
          return itr_->second;
        }

        bool operator==(const const_value_iterator& rhs) const {
          return itr_ == rhs.itr_;
        }

        bool operator!=(const const_value_iterator& rhs) const {
          return itr_ != rhs.itr_;
        }

      private:
        typename map_type::const_iterator itr_; 
    };

    const_key_iterator key_begin() const {
      return const_key_iterator(Map::begin());
    }

    const_key_iterator key_cbegin() const {
      return const_key_iterator(Map::cbegin());
    }

    const_key_iterator key_end() const {
      return const_key_iterator(Map::end());
    }

    const_key_iterator key_cend() const {
      return const_key_iterator(Map::cend());
    }

    value_iterator value_begin() {
      return value_iterator(Map::begin());
    }

    const_value_iterator value_begin() const {
      return const_value_iterator(Map::begin());
    }

    const_value_iterator value_cbegin() const {
      return const_value_iterator(Map::cbegin());
    }

    value_iterator value_end() {
      return value_iterator(Map::end());
    }

    const_value_iterator value_end() const {
      return const_value_iterator(Map::end());
    }

    const_value_iterator value_cend() const {
      return const_value_iterator(Map::cend());
    }

    typename map_type::mapped_type& assert_at(const typename map_type::key_type& k) {
      assert(Map::find(k) != Map::end() && "Unrecognized key!");
      return Map::at(k);
    }

    const typename map_type::mapped_type& assert_at(const typename map_type::key_type& k) const {
      assert(Map::find(k) != Map::end() && "Unrecognized key!");
      return Map::at(k);
    }

    typename map_type::size_type assert_erase(const typename map_type::key_type& k) {
      assert(Map::find(k) != Map::end() && "Unrecognized key!");
      return Map::erase(k);
    }
};

} // namespace cpputil

#endif

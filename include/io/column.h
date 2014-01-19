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

#ifndef CPPUTIL_INCLUDE_IO_COLUMN_H
#define CPPUTIL_INCLUDE_IO_COLUMN_H

#include <algorithm>
#include <streambuf>
#include <string>
#include <vector>

#include <iostream>

namespace cpputil {

class Column {
 public:
  Column() :
    padding_(1), sb_(0) { }

  Column& padding(size_t p) {
    padding_ = p;
    return *this;
  }

  void operator()(std::streambuf* sb, char c) {
    sb_ = sb;

    if (text_.empty()) {
      text_.resize(1);
    }
    auto& col = text_.back();
    if (col.empty()) {
      col.resize(1);
    }

    if (c == '\n') {
      col.resize(col.size() + 1);
    } else {
      col.back().push_back(c);
    }
  }

  Column& next() {
    text_.resize(text_.size() + 1);
    return *this;
  }

  Column& done() {
    if (sb_ == 0) {
      return *this;
    }

    size_t height = 0;
    std::vector<size_t> width;

    for (const auto& col : text_) {
      if (col.size() > height) {
        height = col.size();
      }

      width.push_back(0);
      for (const auto& line : col)
        if (line.size() > width.back()) {
          width.back() = line.size();
        }
    }

    for (size_t i = 0; i < height; ++i) {
      for (size_t c = 0, ce = text_.size(); c < ce; ++c) {
        const auto& col = text_[c];
        if (col.size() <= i) {
          for (size_t j = 0; j < width[c]; ++j) {
            sb_->sputc(' ');
          }
        } else {
          const auto& line = col[i];
          size_t j = 0;
          for (size_t je = line.size(); j < je; ++j) {
            sb_->sputc(line[j]);
          }
          for (; j < width[c]; ++j) {
            sb_->sputc(' ');
          }
        }
        for (size_t j = 0; j < padding_; ++j) {
          sb_->sputc(' ');
        }
      }

      sb_->sputc('\n');
    }

    sb_->pubsync();
    text_.clear();

    return *this;
  }

 private:
  size_t padding_;
  std::vector<std::vector<std::vector<char>>> text_;
  std::streambuf* sb_;
};

} // namespace cpputil

#endif

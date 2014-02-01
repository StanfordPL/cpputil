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

#ifndef CPPUTIL_INCLUDE_IO_WRAP_H
#define CPPUTIL_INCLUDE_IO_WRAP_H

#include <cctype>
#include <streambuf>
#include <string>

namespace cpputil {

class Wrap {
 public:
  Wrap() :
    limit_(80), current_(0) { }

  Wrap& limit(size_t p) {
    limit_ = p;
    return *this;
  }

  void operator()(std::streambuf* sb, char c) {
		if (isgraph(c)) {
			word_ += c;
		} else {
			const auto next = current_ + word_.length();
			const auto space = isblank(c);

			if (next < limit_) {
				write(sb, word_);
				sb->sputc(c);
				current_ = space ? current_ + word_.length() + 1 : 0;
			} else if ( next == limit_ ) {
				write(sb, word_);
				sb->sputc('\n');
				current_  = 0;
			} else {
				sb->sputc('\n');
				write(sb, word_);
				sb->sputc(c);
				current_ = word_.length() + (space ? 1 : 0);
			}
			word_ = "";
		}
  }

 private:
  size_t limit_;
	size_t current_;
	std::string word_;

	void write(std::streambuf* sb, const std::string& word) {
		for ( auto l : word ) {
			sb->sputc(l);
		}
	}
};

} // namespace cpputil

#endif


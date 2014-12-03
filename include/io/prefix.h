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

#ifndef CPPUTIL_INCLUDE_IO_PREFIX_H
#define CPPUTIL_INCLUDE_IO_PREFIX_H

#include <string>

namespace cpputil {

class Prefix {
 public:
  Prefix() : prefix_(""), pending_(true) { }

	Prefix& prefix(const std::string& p) {
		prefix_ = p;
		return *this;
	}

  void operator()(std::streambuf* sb, char c) {
		if (pending_) {
			for (auto p : prefix_) {
				sb->sputc(p);
			}
			pending_ = false;
		}
		if (c == '\n') {
			pending_ = true;
		}
		sb->sputc(c);
	}

 private:
	std::string prefix_;
	bool pending_;
};

} // namespace cpputil

#endif

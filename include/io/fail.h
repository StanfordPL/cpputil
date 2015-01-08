// Copyright 2015 eric schkufza
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

#ifndef CPPUTIL_INCLUDE_IO_FAIL_H
#define CPPUTIL_INCLUDE_IO_FAIL_H

#include <iostream>
#include <sstream>

namespace cpputil {

inline int __fail_msg_idx() {
	static const int idx = std::ios::xalloc();
	return idx;
}

inline bool failed(std::istream& is) {
	return is.fail();
}

inline std::ostringstream& fail(std::istream& is) {
	auto& p = is.pword(__fail_msg_idx());
	if (p == nullptr) {
		p = (void*) new std::ostringstream();
	}
	auto ss = static_cast<std::ostringstream*>(p);

	is.setstate(std::ios::failbit);
	return *ss;
}

inline std::string fail_msg(std::istream& is) {
	auto& p = is.pword(__fail_msg_idx());
	if (p == nullptr) {
		p = (void*) new std::ostringstream();
	}
	const auto& ss = static_cast<std::ostringstream*>(p);

	return ss->str();
}

inline bool failed(std::ostream& os) {
	return os.fail();
}

inline std::ostringstream& fail(std::ostream& os) {
	auto& p = os.pword(__fail_msg_idx());
	if (p == nullptr) {
		p = (void*) new std::ostringstream();
	}
	auto ss = static_cast<std::ostringstream*>(p);

	os.setstate(std::ios::failbit);
	return *ss;
}

inline std::string fail_msg(std::ostream& os) {
	auto& p = os.pword(__fail_msg_idx());
	if (p == nullptr) {
		p = (void*) new std::ostringstream();
	}
	const auto& ss = static_cast<std::ostringstream*>(p);

	return ss->str();
}

} // namespace cpputil

#endif

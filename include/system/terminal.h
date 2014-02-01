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

#ifndef CPPUTIL_INCLUDE_SYSTEM_TERMINAL_H
#define CPPUTIL_INCLUDE_SYSTEM_TERMINAL_H

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <streambuf>

#include "include/io/filterbuf.h"

namespace cpputil {

class Terminal : public std::ostream {
	private:
		struct Filter {
			Filter() : result_(-1) { }

			void operator()(std::streambuf* sb, char c) {
				if ( c == '\n' ) {
					auto strbuf = (std::stringbuf*) sb;
					result_ = system(strbuf->str().c_str());
					strbuf->str(std::string());
				} else {
					sb->sputc(c);
				}
			}
			
			int result_;
		};

	public:
		Terminal() : std::ostream(&buf_), buf_(&strbuf_) { }

		virtual ~Terminal() { }

		int result() {
			return buf_.filter().result_;
		}

	private:
		std::stringbuf strbuf_;
		ofilterbuf<Filter> buf_;	
};

} // namespace cpputil

#endif

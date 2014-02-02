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

#ifndef CPPUTIL_INCLUDE_COMMAND_LINE_HEADING_H
#define CPPUTIL_INCLUDE_COMMAND_LINE_HEADING_H

#include <string>

#include "include/command_line/arg_registry.h"
#include "include/patterns/singleton.h"

namespace cpputil {

class Heading {
	public:
		static Heading& create(const std::string& text) {
			return *(new Heading(text));
		}

	private:
		/** Creating a singleton of this class will ensure Headings aren't leaked. */
		struct HeadingCleanup {
			~HeadingCleanup() {
				for ( auto h : Singleton<ArgRegistry>::get().headings_ ) {
					delete h;
				}
			}
		};

		Heading(const std::string& text) {
			auto& ar = Singleton<ArgRegistry>::get();
			ar.insert(this, text);
			Singleton<HeadingCleanup>::get();
		}
};

} // namespace cpputil

#endif

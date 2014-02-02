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

#ifndef CPPUTIL_INCLUDE_COMMAND_LINE_ARG_GROUP_H
#define CPPUTIL_INCLUDE_COMMAND_LINE_ARG_GROUP_H

#include <string>
#include <vector>

namespace cpputil {

class Arg;

class ArgGroup {
	friend class ArgRegistry;
	friend class Args;

	public:
		const std::string& heading() const {
			return heading_;
		}

		typedef std::vector<Arg*>::const_iterator arg_iterator;

		arg_iterator arg_begin() const {
			return args_.begin();
		}

		arg_iterator arg_end() const {
			return args_.end();
		}

	private:
		ArgGroup(const std::string& heading) : heading_{heading} { }

		std::string heading_;
		std::vector<Arg*> args_;
};

} // namespace cpputil

#endif

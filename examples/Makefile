# Copyright 2013 eric schkufza
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

##### CONSTANT DEFINITIONS

GCC = ccache g++ -std=c++11 -mavx -mavx2 -mbmi -mbmi2 -mpopcnt 
OPT = -Werror -Wextra -pedantic -O3
INC = -I../
LIB = 
EX  = command_line/command_line \
			container/bijection \
			container/bit_array \
			container/bit_vector \
			container/maputil \
			container/tokenizer \
			debug/stl_print \
			io/abort \
			io/column \
			io/console \
			io/fail \
			io/filterstream \
			io/indent \
			io/line_comment \
			io/multistream \
			io/prefix \
			io/redact \
			io/redirectstream \
			io/shunt \
			io/nopstream \
			io/wrap \
			lazy/thunk \
			math/online_stats \
			memory/interner \
			meta/indices \
			patterns/singleton \
			serialize/hex \
			serialize/line \
			serialize/text \
			signal/debug_handler \
			system/terminal

##### TOP LEVEL TARGETS

all: $(EX)

##### BUILD TARGETS

%: %.cc 
	$(GCC) $(OPT) $< -o $@ $(INC) $(LIB)

##### CLEAN TARGETS

clean:
	rm -f $(EX)
	rm -rf command_line/*.dSYM
	rm -rf container/*.dSYM
	rm -rf io/*.dSYM
	rm -rf memory/*.dSYM
	rm -rf patterns/*.dSYM
	rm -rf serialize/*.dSYM
	rm -rf signal/*.dSYM

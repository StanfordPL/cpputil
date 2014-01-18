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

GCC = ccache g++ -std=c++0x
OPT = -Werror -O3
INC = -I../
LIB = 
EX  = container/bijection \
			container/maputil \
			container/tokenizer \
			io/filterstream \
			io/indent \
			io/multistream \
			io/redact \
			io/redirectstream \
			io/shunt \
			io/nopstream \
			memory/interner \
			patterns/singleton \
			signal/debug_handler

##### TOP LEVEL TARGETS

all: $(EX)

##### BUILD TARGETS

%: %.cc 
	$(GCC) $(OPT) $< -o $@ $(INC) $(LIB)

##### CLEAN TARGETS

clean:
	rm -f $(EX)

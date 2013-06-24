# Copyright 2013 eric schkufza

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

##### CONSTANT DEFINITIONS

GCC = ccache g++ 
OPT = -Werror -g -O3 -std=c++0x 
INC = "-I../"
LIB = -lpthread -lrt
EX = args bijection column_printer interner maputil sig_handler singleton \
		 thread timer tokenizer

##### TOP LEVEL TARGETS

all: $(EX)

##### BUILD TARGETS

%: %.cc 
	$(GCC) $(OPT) $< -o $@ $(INC) $(LIB)

##### CLEAN TARGETS

clean:
	rm -f $(EX)

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

DOC=doc/html

##### TOP LEVEL TARGETS

all: $(DOC)

##### DOCUMENTATION TARGETS

doc/html: src/doxyfile src/* src/mainpage.dox
	doxygen src/doxyfile

src/mainpage.dox: README.txt	
	echo "/**" > src/mainpage.dox &&\
	echo \\mainpage >> src/mainpage.dox &&\
	echo "\\\verbatim" >> src/mainpage.dox &&\
	cat README.txt >> src/mainpage.dox &&\
	echo \\endverbatim >> src/mainpage.dox &&\
	echo "*/" >> src/mainpage.dox

##### ASTYLE TARGETS

astyle: 
	astyle -r include/*.h
	astyle -r examples/*.cc

##### CLEAN TARGETS

clean:
	rm -rf $(DOC) src/mainpage.dox
	rm -f `ls -R examples/*/*.orig`
	rm -f `ls -R include/*/*.orig`
	make -C examples clean

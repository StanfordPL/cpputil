/*
Copyright 2013 eric schkufza

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <iostream>
#include <string>

#include "src/bijection.h"

using namespace cpputil;
using namespace std;

int main() {
  Bijection<string, int> b;

	b.insert(std::make_pair("Hello", 1));
	b.insert(std::make_pair("World", 2));

	cout << "[ ";
	for ( const auto& p : b ) 
		cout << "(" << p.first << " " << p.second << ") ";
	cout << "]" << endl;

	const auto itr1 = b.domain_find("Hello");
	cout << "(" << itr1->first << " " << itr1->second << ")" << endl;
	const auto itr2 = b.range_find(2);
	cout << "(" << itr2->first << " " << itr2->second << ")" << endl;

  return 0;
}


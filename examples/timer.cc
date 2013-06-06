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

#include "src/timer.h"

using namespace cpputil;
using namespace std;

int main() {
	Timer t;
	t.start();
	for ( int i = 0; i < 12345678; ++i );
	t.stop();

	cout << t.sec() << " seconds elapsed" << endl;
	cout << t.nsec() << " nanoseconds elapsed" << endl;

  return 0;
}


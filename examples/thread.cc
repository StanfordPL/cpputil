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

#include "include/thread.h"

using namespace cpputil;
using namespace std;

class PrintThread : public Thread {
	public:
		PrintThread() : Thread() { }

	protected:
		virtual void run() {
			for ( int i = 0; i < 10; ++i )
				cout << id() << ": " << i << endl;
		}
};

int main() {
	int N = 2;
	PrintThread ts[N];
	for ( int i = 0; i < N; ++i )
		ts[i].start();
	for ( int i = 0; i < N; ++i )
		ts[i].join();

  return 0;
}


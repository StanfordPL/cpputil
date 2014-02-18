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

#include <iostream>

#include "include/math/online_stats.h"

using namespace cpputil;
using namespace std;

int main() {
	OnlineStats<float> os;
	for ( size_t i = 0; i < 10; ++i ) {
		os.push_back(i);
	}

	float mean = 0;
	float var = 0;
	for ( size_t i = 0; i < 10; ++i ) {
		mean += i;
	}
	mean /= 10;
	for ( size_t i = 0; i < 10; ++i ) {
		var += (i-mean) * (i-mean);
	}
	var /= 9;

	cout << "mean = " << os.mean() << " (should be " << mean << ")" << endl;
	cout << "sig2 = " << os.variance() << " (should be " << var << ")" << endl;

	return 0;
}

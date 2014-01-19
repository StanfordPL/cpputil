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
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "include/serialize/text.h"

using namespace cpputil;
using namespace std;

struct C {
	int x;
	char c;
	double d;
	string s;
};

template <char Open, char Close, char Quote>
struct TextWriter<C, Open, Close, Quote> {
	void operator()(ostream& os, const C& c) {
		os << Open;
		TextWriter<int,Open,Close,Quote>()(os, c.x);
	 	os << " ";
		TextWriter<char,Open,Close,Quote>()(os, c.c);
	 	os << " ";
		TextWriter<double,Open,Close,Quote>()(os, c.d);
	 	os << " ";
		TextWriter<string,Open,Close,Quote>()(os, c.s);
	 	os << Close;
	}
};

template <char Open, char Close, char Quote>
struct TextReader<C, Open, Close, Quote> {
	void operator()(istream& is, C& c) {
		is.get();
		TextReader<int,Open,Close,Quote>()(is, c.x);
		is.get();
		TextReader<char,Open,Close,Quote>()(is, c.c);
		is.get();
		TextReader<double,Open,Close,Quote>()(is, c.d);
		is.get();
		TextReader<string,Open,Close,Quote>()(is, c.s);
		is.get();
	}
};

template <typename T>
ostream& operator<<(ostream& os, const T& t) {
	TextWriter<T> tw;
	tw(os, t);
	return os;
}

template <typename T>
istream& operator>>(istream& is, T& t) {
	TextReader<T> tr;
	tr(is, t);
	return is;
}

int main() {
	C c {1,'c',2.0,"Hello"};
	vector<int> v {1,2};
	list<decltype(v)> l {v,v};
	map<decltype(l), vector<C>> m {{l,{c}}};
	pair<decltype(m), short> p {m,3};

	stringstream ss;
	ss << p << endl;

	decltype(p) p2;
	ss >> p2;

	cout << p << endl;
	cout << p2 << endl;

	return 0;
};

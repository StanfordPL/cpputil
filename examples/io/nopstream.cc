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

#include "include/io/nopstream.h"

using namespace cpputil;
using namespace std;

struct C {
	int x_; 
  int y_;
  int z_;
};

istream& operator>>(istream& is, C& c) { 
  is >> c.x_ >> c.y_ >> c.z_; 
  return is; 
}

ostream& operator<<(ostream& os, const C& c) { 
  os << c.x_ << c.y_ << c.z_ << endl; 
  return os; 
}

int main() {
  bool b;
  short s;
  unsigned short us;
  int i;
  unsigned int ui;
  long l;
  unsigned long ul;
  float f;
  double d;
  long double ld;
  void* v;
  char c;
  signed char sc;
  unsigned char uc;
  char* ch;
  signed char* scp;
  unsigned char* ucp;
	C udt;

	inopstream ins(cin);
  ins >> b;
  ins >> s;
  ins >> us;
  ins >> i;
  ins >> ui;
  ins >> l;
  ins >> ul;
  ins >> f;
  ins >> d;
  ins >> ld;
  ins >> v;
  ins >> cin.rdbuf();
  ins >> cin;
  ins >> c;
  ins >> sc;
  ins >> uc;
  ins >> ch;
  ins >> scp;
  ins >> ucp;
	ins >> udt;

	onopstream ons(cout);
  ons << b;
  ons << s;
  ons << us;
  ons << i;
  ons << ui;
  ons << l;
  ons << ul;
  ons << f;
  ons << d;
  ons << ld;
  ons << v;
  ons << cout.rdbuf();
  ons << cout;
  ons << c;
  ons << sc;
  ons << uc;
  ons << ch;
  ons << scp;
  ons << ucp;
  ons << udt;

  cout << "If you didn't type anything or see anything, this works!" << endl;

	return 0;
}


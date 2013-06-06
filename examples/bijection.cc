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



  return 0;
}


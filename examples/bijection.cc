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


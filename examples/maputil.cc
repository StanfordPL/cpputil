#include <iostream>
#include <map>

#include "src/maputil.h"

using namespace cpputil;
using namespace std;

int main() {
	CppUtilMap<map<int, char>> m;
	for ( int i = 0; i < 5; ++i )
		m[i] = 'a'+i;

	cout << "Pair iteration: [ ";
	for ( const auto& i : m )
		cout << "(" << i.first << "," << i.second << ") ";
	cout << "]" << endl;

	cout << "Key iteration: [ ";
	for ( auto i = m.key_begin(), ie = m.key_end(); i != ie; ++i )
		cout << *i << " ";
	cout << "]" << endl;

	cout << "Value iteration: [ ";
	for ( auto i = m.value_begin(), ie = m.value_end(); i != ie; ++i )
		cout << *i << " ";
	cout << "]" << endl;

	return 0;
}

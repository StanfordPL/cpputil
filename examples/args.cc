#include <iostream>
#include "src/args.h"

using namespace cpputil;
using namespace std;

auto& c = FlagArg::create('c')
	.alternate("cunt")
	.description("What an ugly word!");

auto& d = ValueArg<int>::create('d')
	.default_val(10)
	.alternate("dog")
	.description("I love dogs!")
	.parse_error("OMG YOU MORON!");

auto& f = RangeArg<double>::create('f')
	.default_val(1.0)
	.alternate("fudge")
	.range(0.9, 1.1);


int main(int argc, char** argv) {
	Args::read(argc, argv);
	cout << Args::usage() << endl;

	if ( c ) {
		cout << "YOU SET THE CUNT FLAG!" << endl;
	} else {
		cout << "YOU DIDNT SET THE CUNT FLAG!" << endl;
	}

	cout << "D = " << d << endl;

	return 0;
}

#include <iostream>
#include "src/args.h"

using namespace cpputil;
using namespace std;

auto& help_flag = FlagArg::create('h')
	.alternate("help");

auto& i = ValueArg<int>::create('i')
	.default_val(10)
	.alternate("int");

auto& d = FileArg<double>::create('d')
	.default_val(1.0)
	.alternate("double");

int main(int argc, char** argv) {
	Args::read(argc, argv);

	if ( help_flag )
		cout << Args::usage() << endl;

	return 0;
}

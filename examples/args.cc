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

	if ( help_flag ) {
		cout << "Usage: " << endl;
		cout << Args::usage(2) << endl;
	}
	else
		cout << "Try typing -h or --help" << endl;

	cout << "I = " << i << endl;
	cout << "D = " << d << endl;

	for ( auto i = Args::unrecognized_begin(), ie = Args::unrecognized_end(); i != ie; ++i )
		cout << "Unrecognized input: " << *i << endl;
	for ( auto i = Args::anonymous_begin(), ie = Args::anonymous_end(); i != ie; ++i )
		cout << "Anonymous input: " << *i << endl;

	return 0;
}
